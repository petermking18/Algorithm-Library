#include "SearchAlgorithms.h"

pair<vector<int>,int> SearchAlgorithms::matrixDFSIterative(vector<vector<pair<bool, double>>>& mat, int src, int dest,vector<tuple<double,double,double>>& pos) {
    ///Referenced from https://www.geeksforgeeks.org/iterative-depth-first-traversal/
    vector<bool> visited(mat.size(),false);
    stack<int> stack;
    vector<int> path;
    int nodesExplored = 1;//initialize to 1 for source node

    int curr = src;//set current node to source node
    stack.push(curr);//push source node to stack

    while(!stack.empty()){
        curr = stack.top();
        if(curr == dest)
            break;
        stack.pop();

        if(!visited[curr]){
            visited[curr] = true;
            path.push_back(curr);
        }

        bool found = false;
        for(int i = 1; i < mat[curr].size(); i++){
            if(mat[curr][i].first == true && i == dest){
                found = true;
                path.push_back(i);
                break;
            }
            if(mat[curr][i].first == true && !visited[i]){
                stack.push(i);
                nodesExplored++;
            }
        }
        if(found) {
            break;
        }
    }
    if(path[path.size()-1] != dest)
        path[0] = -1;
    return make_pair(path,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::matrixDFSRecursive(vector<vector<pair<bool, double>>>& mat, int src, int dest,vector<tuple<double,double,double>>& pos) {
    ///Referenced from https://www.geeksforgeeks.org/iterative-depth-first-traversal/
    vector<bool> visited(mat.size(),false);
    stack<int> stack;
    vector<int> path;
    int nodesExplored = 1;//initialize to 1 for source node

    int curr = src;//set current node to source node
    stack.push(curr);//push source node to stack

    pair<vector<int>,int> result = matrixDFSRecursiveUtil(mat,src,dest,curr,nodesExplored,stack,path,visited);
    path = result.first;
    nodesExplored = result.second;
    if(path[path.size()-1] != dest)
        path[0] = -1;
    return make_pair(path,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::matrixDFSRecursiveUtil(vector<vector<pair<bool, double>>>& mat, int& src,int& dest, int & curr,int & nodesExplored,stack<int> & stack, vector<int> & path, vector<bool> & visited) {
    curr = stack.top();
    if(curr == dest)
        return make_pair(path,nodesExplored);
    stack.pop();

    if(!visited[curr]){
        visited[curr] = true;
        path.push_back(curr);
    }

    bool found = false;
    for(int i = 0; i < mat[curr].size(); i++){
        if(mat[curr][i].first == true && i == dest){
            found = true;
            path.push_back(i);
            break;
        }
        if(mat[curr][i].first == true && !visited[i]){
            stack.push(i);
            nodesExplored++;
        }
    }
    if(!found) {
        pair<vector<int>,int> result = matrixDFSRecursiveUtil(mat, src, dest, curr, nodesExplored, stack, path, visited);
        return result;
    }
    return make_pair(path,nodesExplored);
}

pair<vector<int>,int> SearchAlgorithms::alistDFSIterative(vector<list<pair<int, double>>>& alist, int src, int dest,vector<tuple<double,double,double>>& pos) {
    ///Referenced from https://www.geeksforgeeks.org/iterative-depth-first-traversal/
    vector<bool> visited(alist.size(),false);
    stack<int> stack;
    vector<int> path;
    int nodesExplored = 0;

    int curr = src;//set current node to source node
    stack.push(curr);//push source node to stack

    while(!stack.empty()){
        nodesExplored++;
        curr = stack.top();
        if(curr == dest)
            break;
        stack.pop();

        if(!visited[curr]){
            visited[curr] = true;
            path.push_back(curr);
        }

        bool found = false;
        for(auto i = alist[curr].begin(); i != alist[curr].end(); i++) {
            if(i->first == dest) {
                found = true;
                path.push_back(i->first);
                break;
            }
            if (!visited[i->first]) {
                stack.push(i->first);
            }
        }
        if(found) {
            break;
        }
    }
    if(path[path.size()-1] != dest)
        path[0] = -1;
    return make_pair(path,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::alistDFSRecursive(vector<list<pair<int, double>>>& alist, int src, int dest,vector<tuple<double,double,double>>& pos) {
    ///Referenced from https://www.geeksforgeeks.org/iterative-depth-first-traversal/
    vector<bool> visited(alist.size(),false);
    stack<int> stack;
    vector<int> path;
    int nodesExplored = 0;

    int curr = src;//set current node to source node
    stack.push(curr);//push source node to stack

    pair<vector<int>,int> result = alistDFSRecursiveUtil(alist,src,dest,curr,nodesExplored,stack,path,visited);
    path = result.first;
    nodesExplored = result.second;
    if(path[path.size()-1] != dest)
        path[0] = -1;
    return make_pair(path,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::alistDFSRecursiveUtil(vector<list<pair<int, double>>>& alist, int& src,int& dest, int& curr, int& nodesExplored,stack<int>& stack,vector<int>& path, vector<bool>& visited) {
    nodesExplored++;
    curr = stack.top();
    if(curr == dest)
        return make_pair(path,nodesExplored);
    stack.pop();

    if(!visited[curr]){
        visited[curr] = true;
        path.push_back(curr);
    }

    bool found = false;
    for(auto i = alist[curr].begin(); i != alist[curr].end(); i++) {
        if(i->first == dest) {
            found = true;
            path.push_back(i->first);
            break;
        }
        if (!visited[i->first]) {
            stack.push(i->first);
        }
    }
    if(!found) {
        pair<vector<int>,int> result = alistDFSRecursiveUtil(alist, src, dest, curr, nodesExplored, stack, path, visited);
        return result;
    }
    return make_pair(path,nodesExplored);
}

pair<vector<int>,int> SearchAlgorithms::matrixBFSIterative(vector<vector<pair<bool, double>>>& mat,int src,int dest,vector<tuple<double,double,double>>& pos){
    //////Referenced from https://www.geeksforgeeks.org/print-paths-given-source-destination-using-bfs/
    vector<bool> visited(mat.size(),false);
    queue<vector<int>> queue;
    int nodesExplored = 0;
    vector<int> firstPath;
    firstPath.push_back(src);
    queue.push(firstPath);

    while(!queue.empty()){
        nodesExplored++;
        vector<int> currPath = queue.front();
        queue.pop();
        if(currPath[currPath.size()-1] == dest) return make_pair(currPath,nodesExplored);
        for(int i = 0; i < mat[currPath[currPath.size()-1]].size(); i++){
            if(mat[currPath[currPath.size()-1]][i].first){
                bool contains = false;
                for (int p = 0; p < currPath.size(); p++) if (currPath[p] == i) contains = true;
                if (!contains && !visited[i]) {
                    vector<int> newPath = currPath;
                    newPath.push_back(i);
                    queue.push(newPath);
                    visited[i] = true;
                }
            }
        }
    }
    //In the case that no path is found
    vector<int> returnPath;
    returnPath.push_back(-1);
    return make_pair(returnPath,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::matrixBFSRecursive(vector<vector<pair<bool,double>>>& mat,int src,int dest,vector<tuple<double,double,double>>& pos){
    //////Referenced from https://www.geeksforgeeks.org/print-paths-given-source-destination-using-bfs/
    vector<bool> visited(mat.size(),false);
    queue<vector<int>> queue;
    int nodesExplored = 0;
    vector<int> firstPath;
    firstPath.push_back(src);
    queue.push(firstPath);

    pair<vector<int>,int> result = matrixBFSRecursiveUtil(mat,src,dest,nodesExplored,queue,visited);

    //In the case that no path is found
    vector<int> returnPath = result.first;
    nodesExplored = result.second;
    if(returnPath[returnPath.size()-1] != dest) returnPath[0] = -1;
    return make_pair(returnPath,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::matrixBFSRecursiveUtil(vector<vector<pair<bool,double>>>& mat,int& src,int& dest,int& nodesExplored,queue<vector<int>>& queue,vector<bool>& visited){
        nodesExplored++;
        vector<int> currPath = queue.front();
        queue.pop();
        if(currPath[currPath.size()-1] == dest) return make_pair(currPath,nodesExplored);
        for(int i = 0; i < mat[currPath[currPath.size()-1]].size(); i++) {
            if (mat[currPath[currPath.size() - 1]][i].first) {
                bool contains = false;
                for (int p = 0; p < currPath.size(); p++) if (currPath[p] == i) contains = true;
                if (!contains && !visited[i]) {
                    vector<int> newPath = currPath;
                    newPath.push_back(i);
                    queue.push(newPath);
                    visited[i] = true;
                }
            }
        }
        return matrixBFSRecursiveUtil(mat,src,dest,nodesExplored,queue,visited);
}

pair<vector<int>,int> SearchAlgorithms::alistBFSIterative(vector<list<pair<int, double>>>& alist, int src, int dest,vector<tuple<double,double,double>>& pos) {
    //////Referenced from https://www.geeksforgeeks.org/print-paths-given-source-destination-using-bfs/
    vector<bool> visited(alist.size(),false);
    queue<vector<int>> queue;
    int nodesExplored = 0;
    vector<int> firstPath;
    firstPath.push_back(src);
    queue.push(firstPath);

    while(!queue.empty()){
        nodesExplored++;
        vector<int> currPath = queue.front();
        queue.pop();
        if(currPath[currPath.size()-1] == dest) return make_pair(currPath,nodesExplored);
        for(auto i = alist[currPath[currPath.size()-1]].begin(); i != alist[currPath[currPath.size()-1]].end(); i++){
            bool contains = false;
            for(int p = 0; p < currPath.size(); p++) if(currPath[p] == i->first) contains = true;
            if(!contains && !visited[i->first]){
                vector<int> newPath = currPath;
                newPath.push_back(i->first);
                queue.push(newPath);
                visited[i->first] = true;
            }
        }
    }
    //In the case that no path is found
    vector<int> returnPath;
    returnPath.push_back(-1);
    return make_pair(returnPath,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::alistBFSRecursive(vector<list<pair<int, double>>>& alist, int src, int dest,vector<tuple<double,double,double>>& pos) {
    //////Referenced from https://www.geeksforgeeks.org/print-paths-given-source-destination-using-bfs/
    vector<bool> visited(alist.size(),false);
    queue<vector<int>> queue;
    int nodesExplored = 0;
    vector<int> firstPath;
    firstPath.push_back(src);
    queue.push(firstPath);

    pair<vector<int>,int> result = alistBFSRecursiveUtil(alist, src, dest, nodesExplored, queue, visited);

    //In the case that no path is found
    vector<int> returnPath = result.first;
    nodesExplored = result.second;
    if(returnPath[returnPath.size()-1] != dest) returnPath[0] = -1;
    return make_pair(returnPath,nodesExplored);

}
pair<vector<int>,int> SearchAlgorithms::alistBFSRecursiveUtil(vector<list<pair<int,double>>>& alist, int& src,int& dest, int& nodesExplored, queue<vector<int>>& queue,vector<bool>& visited) {
    nodesExplored++;
    vector<int> currPath = queue.front();
    queue.pop();
    if(currPath[currPath.size()-1] == dest) return make_pair(currPath,nodesExplored);
    for(auto i = alist[currPath[currPath.size()-1]].begin(); i != alist[currPath[currPath.size()-1]].end(); i++) {
        bool contains = false;
        for(int p = 0; p < currPath.size(); p++) if(currPath[p] == i->first) contains = true;
        if(!contains && !visited[i->first]){
            vector<int> newPath = currPath;
            newPath.push_back(i->first);
            queue.push(newPath);
            visited[i->first] = true;
        }
    }
    return alistBFSRecursiveUtil(alist,src,dest,nodesExplored,queue,visited);
}

pair<vector<int>,int> SearchAlgorithms::matrixDijkstra(vector<vector<pair<bool, double>>>& mat,int src,int dest,vector<tuple<double, double, double>>& pos) {
    //////Referenced from https://www.tutorialspoint.com/Dijkstra-s-Algorithm-for-Adjacency-List-Representation
    //////and https://algotree.org/algorithms/single_source_shortest_path/dijkstras_shortest_path_c++/
    typedef pair<double,int> p;
    priority_queue<p, vector<p>, greater<p>> pq;

    int n = mat.size();
    vector<double> cost;
    vector<int> prev;
    vector<bool> visited(n, false);

    ///Traversal cost is (edge weight from parent to child) * (positional distance between parent and child)
    auto calcTraversalCost = [&pos](int parentNode,int childNode,double weightToChild) -> double {
        double x1 = get<0>(pos[parentNode]);
        double y1 = get<1>(pos[parentNode]);
        double z1 = get<2>(pos[parentNode]);
        double x2 = get<0>(pos[childNode]);
        double y2 = get<1>(pos[childNode]);
        double z2 = get<2>(pos[childNode]);
        double posDist = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
        return posDist*weightToChild;
    };

    ///Initialize dist and prev and queue
    for(int i = 0; i < n; i++){
        cost.push_back(999999);
        prev.push_back(-1);
    }
    cost[src] = 0;
    pq.push(make_pair(cost[src],src));

    double pathToDestCost = 9999999;
    while(!pq.empty()){
        pair<double,int> parent = pq.top();
        pq.pop();
        double parentCost = parent.first;
        int parentId = parent.second;
        if(parentCost > pathToDestCost) continue;
        if(!visited[parentId]) visited[parentId] = true;
        if(parentId == dest) pathToDestCost = parentCost;

        list<pair<int,double>>::const_iterator child;
        for(int childId = 0; childId < mat[parentId].size(); childId++){
            bool isChild = mat[parentId][childId].first;
            double weightToChild = mat[parentId][childId].second;
            double traversalCost = calcTraversalCost(parentId,childId,weightToChild);
            if(isChild && ((parentCost+traversalCost) < cost[childId])){
                cost[childId] = (parentCost+traversalCost);
                prev[childId] = parentId;
                pq.push(make_pair(cost[childId],childId));
            }
        }
    }

    vector<int> path;
    path.push_back(dest);
    int curr = dest;
    while(curr != src){
        if(curr == -1) break;
        curr = prev[curr];
        path.push_back(curr);
    }

    int nodesExplored = 0;
    for(int i = 1; i < n; i++) if(visited[i]) nodesExplored++;
    reverse(path.begin(),path.end());
    return make_pair(path,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::alistDijkstra(vector<list<pair<int, double>>>& alist, int src, int dest,vector<tuple<double,double,double>>& pos){
    //////Referenced from https://www.tutorialspoint.com/Dijkstra-s-Algorithm-for-Adjacency-List-Representation
    //////and https://algotree.org/algorithms/single_source_shortest_path/dijkstras_shortest_path_c++/
    typedef pair<double,int> p;
    priority_queue<p, vector<p>, greater<p>> pq;

    int n = alist.size();
    vector<double> cost;
    vector<int> prev;
    vector<bool> visited(n, false);

    ///Traversal cost is (edge weight from parent to child) * (positional distance between parent and child)
    auto calcTraversalCost = [&pos,&cost](int parentNode,int childNode,double weightToChild) -> double {
        double x1 = get<0>(pos[parentNode]);
        double y1 = get<1>(pos[parentNode]);
        double z1 = get<2>(pos[parentNode]);
        double x2 = get<0>(pos[childNode]);
        double y2 = get<1>(pos[childNode]);
        double z2 = get<2>(pos[childNode]);
        double posDist = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
        return posDist*weightToChild;
    };

    ///Initialize dist and prev and queue
    for(int i = 0; i < n; i++){
        cost.push_back(999999);
        prev.push_back(-1);
    }
    cost[src] = 0;
    pq.push(make_pair(cost[src],src));

    double pathToDestCost = 9999999;
    while(!pq.empty()){
        pair<double,int> parent = pq.top();
        pq.pop();
        double parentCost = parent.first;
        int parentId = parent.second;
        if(parentCost > pathToDestCost) continue;
        if(!visited[parentId]) visited[parentId] = true;
        if(parentId == dest) {
            pathToDestCost = parentCost;
            //break;///for testing
        }

        list<pair<int,double>>::const_iterator child;
        for(child = alist[parentId].begin(); child != alist[parentId].end(); child++){//for children of current pq node
            int childId = child->first;
            double weightToChild = child->second;
            double traversalCost = calcTraversalCost(parentId,childId,weightToChild);
            if((parentCost+traversalCost) < cost[childId]){
                cost[childId] = (parentCost+traversalCost);
                prev[childId] = parentId;
                pq.push(make_pair(cost[childId],childId));
            }
        }
    }
    vector<int> path;
    path.push_back(dest);
    int curr = dest;
    while(curr != src){
        if(curr == -1) break;
        curr = prev[curr];
        path.push_back(curr);
    }
    int nodesExplored = 0;
    for(int i = 1; i < n; i++) if(visited[i]) nodesExplored++;
    reverse(path.begin(),path.end());
    return make_pair(path,nodesExplored);
}

pair<vector<int>,int> SearchAlgorithms::matrixAstar(vector<vector<pair<bool,double>>>& mat,int src,int dest,vector<tuple<double,double,double>>& pos){
    //////Referenced from https://www.tutorialspoint.com/Dijkstra-s-Algorithm-for-Adjacency-List-Representation
    //////and https://algotree.org/algorithms/single_source_shortest_path/dijkstras_shortest_path_c++/
    //////A* specifics referenced from https://www.geeksforgeeks.org/a-search-algorithm/
    typedef pair<double,int> p;
    priority_queue<p, vector<p>, greater<p>> pq;

    int n = mat.size();
    vector<double> cost;
    vector<int> prev;
    vector<bool> visited(n, false);

    auto calcH = [&pos](int parentNode,int childNode) -> double {
        double x1 = get<0>(pos[parentNode]);
        double y1 = get<1>(pos[parentNode]);
        double z1 = get<2>(pos[parentNode]);
        double x2 = get<0>(pos[childNode]);
        double y2 = get<1>(pos[childNode]);
        double z2 = get<2>(pos[childNode]);
        return sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
    };

    vector<double> hVal;
    hVal.push_back(-1);
    for(int i = 1; i < n; i++) hVal.push_back(calcH(i,dest));

    auto calcTraversalCost = [&pos,&cost](int parentNode,int childNode,double weightToChild) -> double {
        double x1 = get<0>(pos[parentNode]);
        double y1 = get<1>(pos[parentNode]);
        double z1 = get<2>(pos[parentNode]);
        double x2 = get<0>(pos[childNode]);
        double y2 = get<1>(pos[childNode]);
        double z2 = get<2>(pos[childNode]);
        double posDist = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
        return posDist*weightToChild;
    };

    /*///Declare lambda for calculating f value
    auto calcF = [&pos,&dest,&cost](int currNode) -> double {
        double x1 = get<0>(pos[currNode]);
        double y1 = get<1>(pos[currNode]);
        double z1 = get<2>(pos[currNode]);
        double x2 = get<0>(pos[dest]);
        double y2 = get<1>(pos[dest]);
        double z2 = get<2>(pos[dest]);
        double h = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
        double f = cost[currNode]+h;
        return f;
    };*/

    ///Initialize dist and prev and queue
    for(int i = 0; i < n; i++){
        cost.push_back(999999);
        prev.push_back(-1);
    }
    cost[src] = 0;
    pq.push(make_pair(cost[src],src));

    bool found = false;/////remove?
    double pathToDestCost = 99999999;
    while(!pq.empty()){
        pair<double,int> parent = pq.top();//distance/f, parent node id
        pq.pop();
        int parentId = parent.second;
        double parentCost = cost[parentId];
        if(parentCost > pathToDestCost) continue;
        if(!visited[parentId])  visited[parentId] = true;
        if(parentId == dest){
            pathToDestCost = parentCost;
            //break;///for testing
        }

        //list<pair<int,double>>::const_iterator child;//child node id, traversal cost to child from parent
        //for(child = alist[parentId].begin(); child != alist[parentId].end(); child++){//for each child of parent
        for(int childId = 0; childId < mat[parentId].size(); childId++){
            if(!mat[parentId][childId].first) continue;
            //int childId = child->first;
            //double costToChild = child->second;
            double costToChild = mat[parentId][childId].second;
            double traversalCost = calcTraversalCost(parentId,childId,costToChild);
/*            if(childId == dest){
                prev[childId] = parentId;//update the previous of child/dest
                found = true;
                break;
            }*//////remove?
            if((parentCost+traversalCost) < cost[childId]){//if parent+traversal to child < previously stored lowest distance for child, update dist of child to dist of parent + traversal, update prev of child to parent, push child back into pq with f val
                cost[childId] = (parentCost+traversalCost);
                prev[childId] = parentId;
                pq.push(make_pair(cost[childId]+hVal[childId],childId));
            }
        }
        //if(found) break;/////remove?
    }

    vector<int> path;
    path.push_back(dest);
    int curr = dest;
    while(curr != src){
        if(curr == -1) break;
        curr = prev[curr];
        path.push_back(curr);
    }

    int nodesExplored = 0;
    for(int i = 0; i < n; i++) if(visited[i]) nodesExplored++;

    reverse(path.begin(),path.end());
    return make_pair(path,nodesExplored);
}
pair<vector<int>,int> SearchAlgorithms::alistAstar(vector<list<pair<int, double>>>& alist,int src,int dest,vector<tuple<double,double,double>>& pos){
    //////Referenced from https://www.tutorialspoint.com/Dijkstra-s-Algorithm-for-Adjacency-List-Representation
    //////and https://algotree.org/algorithms/single_source_shortest_path/dijkstras_shortest_path_c++/
    //////A* specifics referenced from https://www.geeksforgeeks.org/a-search-algorithm/
    typedef pair<double,int> p;
    priority_queue<p, vector<p>, greater<p>> pq;

    int n = alist.size();
    vector<double> cost;
    vector<int> prev;
    vector<bool> visited(n, false);

    auto calcH = [&pos](int parentNode,int childNode) -> double {
        double x1 = get<0>(pos[parentNode]);
        double y1 = get<1>(pos[parentNode]);
        double z1 = get<2>(pos[parentNode]);
        double x2 = get<0>(pos[childNode]);
        double y2 = get<1>(pos[childNode]);
        double z2 = get<2>(pos[childNode]);
        return sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
    };

    vector<double> hVal;
    hVal.push_back(-1);
    for(int i = 1; i < n; i++){
        hVal.push_back(calcH(i,dest));
    }

    auto calcTraversalCost = [&pos,&cost](int parentNode,int childNode,double weightToChild) -> double {
        double x1 = get<0>(pos[parentNode]);
        double y1 = get<1>(pos[parentNode]);
        double z1 = get<2>(pos[parentNode]);
        double x2 = get<0>(pos[childNode]);
        double y2 = get<1>(pos[childNode]);
        double z2 = get<2>(pos[childNode]);
        double posDist = sqrt(pow((x2-x1),2)+pow((y2-y1),2)+pow((z2-z1),2));
        return posDist*weightToChild;
    };

    ///Initialize dist and prev and queue
    for(int i = 0; i < n; i++){
        cost.push_back(999999);
        prev.push_back(-1);
    }
    cost[src] = 0;
    pq.push(make_pair(cost[src],src));

    double pathToDestCost = 9999999;
    while(!pq.empty()){
        pair<double,int> parent = pq.top();//distance/f, parent node id
        pq.pop();
        int parentId = parent.second;
        double parentCost = cost[parentId];
        if(parentCost > pathToDestCost) continue;
        if(!visited[parentId])  visited[parentId] = true;
        if(parentId == dest) {
            pathToDestCost = parentCost;
            //break;///for testing
        }
        //Finds dest earlier than Dijkstra, but takes a lot more time to find lowest cost path

        list<pair<int,double>>::const_iterator child;//child node id, traversal cost to child from parent
        for(child = alist[parentId].begin(); child != alist[parentId].end(); child++){//for each child of parent
            int childId = child->first;
            double costToChild = child->second;
            double traversalCost = calcTraversalCost(parentId,childId,costToChild);
            if((parentCost+traversalCost) < cost[childId]){//if parent+traversal to child < previously stored lowest distance for child, update dist of child to dist of parent + traversal, update prev of child to parent, push child back into pq with f val
                cost[childId] = (parentCost+traversalCost);
                prev[childId] = parentId;
                //pq.push(make_pair(cost[childId]+hVal[childId],childId));
                pq.push(make_pair(cost[childId]+hVal[childId],childId));
                //pq.push(make_pair(cost[childId]+calcH(childId,dest),childId));
                //pq.push(make_pair(cost[childId]+(sqrt(pow(get<0>(pos[childId])-get<0>(pos[dest]),2)+pow(get<1>(pos[childId])-get<1>(pos[dest]),2))+pow(get<2>(pos[childId])-get<2>(pos[dest]),2)),childId));
            }
        }
    }
    vector<int> path;
    path.push_back(dest);
    int currInPath = dest;
    while(currInPath != src){
        if(currInPath == -1) break;
        currInPath = prev[currInPath];
        path.push_back(currInPath);
    }

    int nodesExplored = 0;
    for(int i = 0; i < n; i++) if(visited[i]) nodesExplored++;

    reverse(path.begin(),path.end());
    return make_pair(path,nodesExplored);
}