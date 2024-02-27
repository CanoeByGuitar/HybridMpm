//
// Created by ChenhuiWang on 2024/2/26.

// Copyright (c) 2024 Tencent. All rights reserved.
//

#ifndef HYBRIDMPM_DATAMANAGER_H
#define HYBRIDMPM_DATAMANAGER_H

#include "DataArray.h"
#include "util/Log.h"
#include <tbb/tbb.h>

namespace DATA {

/**
  An AttributeName stores the name of an attribute, together with its type
  It is used as a convenience to make it so that you only have to state
  the name and the type of the attribute once.
  It also stores the hash value to avoid dynamic memory allocation
  */
template<typename Type> struct AttributeName {
public:
    const std::string name;
    const size_t      hash;

    AttributeName(const char* a)
        : name(a)
        , hash(std::hash<std::string>()(name)) {}

    AttributeName(const std::string& a)
        : name(a)
        , hash(std::hash<std::string>()(name)) {}
};

/**
    DataManager is a database.
    It stores arbitrary number of arrays with arbitrary number of attributes.
    Totally flexible.
    Note that when adding entries, new entries ranges (IDs)
    must be retrived with getNextRange from the database. This is to ensure that
    the entries are stored in the database in a sorted fashion.
    Once created, this class is the only interface of using or modifying entry data.
*/
class DataManager {
public:
    int count;   // the total number of entries
    std::unordered_map<size_t, std::unique_ptr<DataArrayBase>> batches;

    DataManager()
        : count(0) {}

    DataManager(const DataManager&) = delete;

    template<typename Type, typename... Types>
    DataManager(const DataArray<Type>& a, const DataArray<Types>&... b)
        : DataManager(b...) {}

    virtual ~DataManager() {}

    template<typename Type>
    DataArray<Type>& Add(const AttributeName<Type>& a){

    }

    template<typename Type>
    DataArray<Type>& Add(const AttributeName<Type>& a, Range range, std::vector<Type>&& array){
        MPM_ASSERT(range.upper - range.lower == array.size());
        if(range.upper > count){
            count = range.upper;
        }

        auto search = batches.find(a.hash);
        if(search == batches.end()){
            auto r = batches.emplace(a.hash,
                                     std::make_unique<DataArray<Type>>(
                                         a.name, DisjointRanges{range}, std::move(array)
                                         ));
            return dynamic_cast<DataArray<Type>&>(*r.first->second);
        }else {
            MPM_ASSERT(a.name == search->second->name);
            // attribute exists, append data to it
            DataArray<Type>& old = dynamic_cast<DataArray<Type>&>(*search->second);
            old.ranges.Append(range);
            old.array.insert(old.array.end(),
                             std::make_move_iterator(array.begin()),
                             std::make_move_iterator(array.end()));
            array.clear();
            return old;
        }
    }

    template<typename Type>
    DataArray<Type>& Add(const AttributeName<Type>& a, Range range, const std::vector<Type>& array){
        return Add(a, range, std::vector<Type>(array.begin(), array.end()));
    }

    template<typename Type>
    DataArray<Type>& Get(const AttributeName<Type>& a) const {
        auto search = batches.find(a.hash);
        MPM_ASSERT(search != batches.end(), "Could not fine" + a.name);
        return dynamic_cast<DataArray<Type>&>(*search->second);
    }

    Range GetNextRange(int size) const{
        return Range{count, count + size};
    }

//    template <typename Func, typename... Types>
//    void parallel_for(const Func& f, const AttributeName<Types>&... names){
//
//    }


};

}   // namespace DATA



#endif   // HYBRIDMPM_DATAMANAGER_H
