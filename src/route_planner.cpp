#include "route_planner.h"
#include "node_comparer.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    this->start_node = &m_Model.FindClosestNode(start_x, start_y);
    this->end_node = &m_Model.FindClosestNode(end_x, end_y);
}


float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {

    return node->distance(*(this->end_node));
}


void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

    current_node->FindNeighbors();

    for(int i = 0; i < current_node->neighbors.size(); i++)
    {
        current_node->neighbors[i]->parent = current_node;
        current_node->neighbors[i]->g_value = current_node->g_value + current_node->distance(*(current_node->neighbors[i]));
        current_node->neighbors[i]->h_value = CalculateHValue(current_node->neighbors[i]);
        this->open_list.push_back(current_node->neighbors[i]);
        current_node->neighbors[i]->visited = true;
    }
}


RouteModel::Node *RoutePlanner::NextNode() {

    std::sort(this->open_list.begin(), this->open_list.end(), CompareNodeFVal);
    RouteModel::Node *next_node = this->open_list.back();
    this->open_list.pop_back();
    return next_node;
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    this->distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while(current_node->parent != nullptr)
    {
        distance += current_node->distance(*(current_node->parent));
        path_found.push_back(*current_node);

        current_node = current_node->parent;
    }
    path_found.push_back(*(this->start_node));
    std::reverse(path_found.begin(), path_found.end());

    this->distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr; 
    this->start_node->visited = true;
    this->open_list.push_back(this->start_node);

    while(this->open_list.size() > 0)
    {
        current_node = NextNode();
        if(current_node->x == this->end_node->x && current_node->y == this->end_node->y)
        {
            m_Model.path = ConstructFinalPath(current_node);
        }
        else
        {
            AddNeighbors(current_node);
        }
    }

}