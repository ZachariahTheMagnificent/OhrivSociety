#pragma once
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <math\Vector3.h>
#include <math\Line.h>

namespace ai
{
	using Vector3 = math::Vector3<float>;
	using Line = math::Line<float>;

	struct PathNodeTravelInfo final
	{
		void ConnectTo ( const std::size_t travel_info_index, const float new_distance_travelled_squared, const float new_total_travel_cost )
		{
			if ( !calculated )
			{
				calculated = true;
				if ( new_total_travel_cost <= total_travel_cost )
				{
					distance_travelled_squared = new_distance_travelled_squared;
					total_travel_cost = new_total_travel_cost;
					previous_travel_info_index = travel_info_index;
				}
			}
		}

		float distance_travelled_squared { FLT_MAX };
		float distance_to_goal_squared { FLT_MAX };
		float total_travel_cost { FLT_MAX };
		bool calculated { false };
		bool connected_to_start { false };
		std::size_t previous_travel_info_index;
	};

	class PathNode final
	{
	public:
		PathNode ( ) = default;

		void AddNeighbour ( std::size_t travel_info_index, const Vector3 position )
		{
			neighbour_positions_.push_back ( position );
			neighbour_travel_info_.push_back ( travel_info_index );
			new_distance_travelled_squared_cache_.push_back ( float { } );
		}

		void CalculateNeighbours ( std::vector<std::size_t>& calculated_unvisited_nodes_indices, std::vector<PathNodeTravelInfo>& travel_info, const std::size_t self_travel_info_index, const Vector3 position ) const
		{
			const float distance_travelled_squared = travel_info [ self_travel_info_index ].distance_travelled_squared;
			const std::size_t size = neighbour_positions_.size ( );

			for ( std::size_t index = 0; index < size; ++index )
			{
				new_distance_travelled_squared_cache_ [ index ] = ( neighbour_positions_ [ index ] - position ).LengthSquared ( ) + distance_travelled_squared;
			}

			for ( std::size_t index = 0; index < size; ++index )
			{
				const std::size_t travel_info_index = neighbour_travel_info_ [ index ];

				const float new_distance_travelled_squared = new_distance_travelled_squared_cache_ [ index ];
				const float new_total_travel_cost = new_distance_travelled_squared + travel_info [ travel_info_index ].distance_to_goal_squared;

				if ( !travel_info [ travel_info_index ].calculated )
				{
					calculated_unvisited_nodes_indices.push_back ( travel_info_index );
				}

				travel_info [ travel_info_index ].ConnectTo ( self_travel_info_index, new_distance_travelled_squared, new_total_travel_cost );
			}
		}

	private:
		std::vector<Vector3> neighbour_positions_;
		std::vector<std::size_t> neighbour_travel_info_;

		mutable std::vector<float> new_distance_travelled_squared_cache_;
	};

	class PathFinder final
	{
	public:
		void Build ( const std::vector<Vector3>& positions, const std::vector<Line>& line_boundaries )
		{
			const std::size_t num_nodes = positions.size ( );
			const std::size_t num_boundaries = line_boundaries.size ( );

			line_boundaries_.resize ( num_boundaries );

			node_positions_.resize ( num_nodes );
			path_nodes_.resize ( num_nodes );
			calculated_unvisited_nodes_index_cache_.resize ( num_nodes );
			travel_info_cache_.resize ( num_nodes );

			line_boundaries_ = line_boundaries;

			for ( std::size_t index = 0; index < num_nodes; ++index )
			{
				node_positions_ [ index ] = positions [ index ];
			}

			const auto travel_info_begin = travel_info_cache_.begin ( );

			for ( std::size_t index1 = 0; index1 < num_nodes; ++index1 )
			{
				for ( std::size_t index2 = 0; index2 < num_nodes; ++index2 )
				{
					const Vector3 node_position1 = node_positions_ [ index1 ];
					const Vector3 node_position2 = node_positions_ [ index2 ];

					if ( Connected ( node_position1, node_position2 ) )
					{
						path_nodes_ [ index1 ].AddNeighbour ( index2, node_position2 );
						path_nodes_ [ index2 ].AddNeighbour ( index1, node_position1 );
					}
				}
			}
		}

		Vector3 FindNextNodePositionInShortestPath ( const Vector3 starting_position, const Vector3 goal )
		{
			if ( Connected ( starting_position, goal ) )
			{
				return goal;
			}

			const std::size_t num_nodes = node_positions_.size ( );

			//reset travel_info_buffer
			travel_info_cache_.clear ( );
			travel_info_cache_.resize ( num_nodes );

			//Calculate distance to goal for all nodes
			for ( std::size_t index = 0; index < num_nodes; ++index )
			{
				const Vector3 node_to_goal = goal - node_positions_ [ index ];
				travel_info_cache_ [ index ].distance_to_goal_squared = node_to_goal.LengthSquared ( );
			}

			//Find all nodes connected to starting position and add them to the processing array
			calculated_unvisited_nodes_index_cache_.clear ( );
			for ( std::size_t index = 0; index < num_nodes; ++index )
			{
				const Vector3 node_position = node_positions_ [ index ];

				PathNodeTravelInfo& travel_info = travel_info_cache_ [ index ];

				if ( Connected ( starting_position, node_position ) )
				{
					const Vector3 start_to_node = node_position - starting_position;
					travel_info.calculated = true;
					travel_info.connected_to_start = true;
					travel_info.distance_travelled_squared = start_to_node.LengthSquared ( );
					travel_info.total_travel_cost = travel_info.distance_travelled_squared + travel_info.distance_to_goal_squared;
					calculated_unvisited_nodes_index_cache_.push_back ( index );
				}
			}

			//loop until there is nothing else to search
			for ( std::size_t size = calculated_unvisited_nodes_index_cache_.size ( ); size != 0; size = calculated_unvisited_nodes_index_cache_.size ( ) )
			{
				//Get the lowest cost node to calculate neighbours and add any unvisited to the processing array. Then remove it.
				std::size_t index_of_node_to_process = calculated_unvisited_nodes_index_cache_.front ( );
				float total_travel_cost = travel_info_cache_ [ index_of_node_to_process ].total_travel_cost;
				std::size_t element_to_delete_index = 0;
				for ( std::size_t index = 1; index < size; ++index )
				{
					const std::size_t node_index = calculated_unvisited_nodes_index_cache_ [ index ];

					const float new_total_travel_cost = travel_info_cache_ [ node_index ].total_travel_cost;
					if ( new_total_travel_cost < total_travel_cost )
					{
						index_of_node_to_process = node_index;
						total_travel_cost = new_total_travel_cost;
						element_to_delete_index = index;
					}
				}

				calculated_unvisited_nodes_index_cache_.erase ( calculated_unvisited_nodes_index_cache_.begin ( ) + element_to_delete_index );

				//break if node is connected to the goal
				const Vector3 position = node_positions_ [ index_of_node_to_process ];
				const auto travel_info_begin = travel_info_cache_.begin ( );
				if ( Connected ( goal, position ) )
				{
					//backtrack to find next node
					std::vector<PathNodeTravelInfo>::const_iterator current = travel_info_begin + index_of_node_to_process;
					while ( !current->connected_to_start )
					{
						current = travel_info_begin + current->previous_travel_info_index;
					}

					const std::size_t index = current - travel_info_begin;
					return node_positions_ [ index ];
				}

				path_nodes_ [ index_of_node_to_process ].CalculateNeighbours ( calculated_unvisited_nodes_index_cache_, travel_info_cache_, index_of_node_to_process, position );
			}

			return Vector3 { };
		}

	private:
		bool Connected ( const Vector3 position1, const Vector3 position2 );

		std::vector<Line> line_boundaries_;
		std::vector<Vector3> node_positions_;
		std::vector<PathNode> path_nodes_;

		mutable std::vector<std::size_t> calculated_unvisited_nodes_index_cache_;
		mutable std::vector<PathNodeTravelInfo> travel_info_cache_;
	};
}