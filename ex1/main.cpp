#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>


// Problem 1: delete zeroes from the vector. Functions remove + erase
//   eg  result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
// Problem 2: delete zeroes from the vector without standard functions.
// Problem 3: delete columns from the matrix which have zeroes

// Please remind for the control work:
// 1. Reading csv files. Converting string to integer/double std::stod, std::stoi
// 2. set/map (e.g. constructors from vector, count, cycles, find over the set)
// 3. deleting from containers
// 4. converting data types (e.g. integer to double). 10 / 20 = 0



void delete_zeroes_from_columns (std::vector<std::vector <int>> &matrix)
{
}

void delete_zeroes_from_vector ()
{
    std::vector<int> vec  = {1, 0, 2, 0, 3, 0, 4};
    std::vector<int>::iterator it = std::remove(vec.begin(), vec.end(), 0);
    vec.erase(it, vec.end());

    for (int elem : vec)
    {
        std::cout << elem << " ";
    }
}

void set_funcs ()
{
    std::vector<int> vec  = {1, 0, 2, 0, 3, 0, 4};

    // Constructor
    std::set<int> my_set (vec.begin (), vec.end ());

    for (int element : my_set)
    {
        std::cout << element << "\n";
    }

    my_set.insert (10);

    std::vector<int> vec2 = {10, 11, 12, 13};
    for (int element : vec2)
    {
        my_set.insert(element);
    }

    if (my_set.find(10) != my_set.end ())
    {
        // we have element!
    }

    if (my_set.count(10) != 0 )
    {

    }
}

void map_funcs ()
{
    std::map<std::string, int> my_map;
    int i = 10;
    for (std::string name : {"a", "b", "c", "d"})
    {
        my_map[name] = i;
        i += 10;
    }

    for (const std::pair<std::string, int> &element : my_map)
    {
        std::cout << element.first << " " << element.second << "\n";
    }

    std::map<std::string, int>::iterator it = my_map.find ("a");
    if (it != my_map.end ())
    {
        std::cout << it->first << " " << it->second; //key
    }

}

int main ()
{
    return 0;
}





