//
// Created by chenhuiwang on 2024/1/5.
//

#ifndef HYBRIDMPM_DS_H
#define HYBRIDMPM_DS_H

#include "utils.h"
#include <memory>
#include <unordered_map>
#include <vector>

/**
    DataArray represents a continuous memory block of entry data.
    It has two members.
    1. ranges.
        This is an array of sorted ranges of global entry IDs,
        inclusive on the left, exclusive on the right.
        For example, [0,3), [6,8) means this batch stores data for entries
        0,1,2,6,7
    2. array.
        This is an array of data with any type. E.g., for positions.
        The array stores contiguous data for the entities in the ranges
        Continuing the example if the array is [1, 2, 3, 4, 5]
        then the entries and correspoding values are as follows
        |Entry |   ValueId |   Value |
        |  0   |     0     |     1   |
        |  1   |     1     |     2   |
        |  2   |     2     |     3   |
        |  3   |    NA     |    NA   |
        |  4   |    NA     |    NA   |
        |  5   |    NA     |    NA   |
        |  6   |     3     |     4   |
        |  7   |     4     |     5   |

*/
class DataArrayBase {
public:
    virtual ~DataArrayBase() = default;
};

template<typename T> class DataArray : public DataArrayBase {
public:
    explicit DataArray(std::vector<T>&& array)
        : m_array(std::move(array)) {}

    T& operator[](size_t i) { return m_array[i]; }

    size_t size() const { return m_array.size(); }

private:
    std::vector<T> m_array;
};


/// for now:
/// all entries have the same number of elements
/// entry  |  idx0 | idx1 | ... | idxn
/// mass   |  m0   | m1   | ... | m2
/// v      |  v0   | v1   | ... | v2
class DataManager {
public:
    DataManager()
        : m_count(0) {}

    DataManager(const DataManager&) = delete;




    template<typename T> void Add(const std::string& name, std::vector<T>&& data) {
        if (m_count == 0) {
            m_count = data.size();
        } else {
            MPM_ASSERT(m_count == data.size(),
                       "The input data length is not the same as current count!");
        }
        m_data[name] = std::make_unique<DataArrayBase>(DataArray<T>(std::move(data)));
    }

    template<typename T> DataArray<T>& Get(const std::string& name) const {
        auto search = m_data.find(name);
        MPM_ASSERT(search != m_data.end(), "Cannot find: " + name);
        return dynamic_cast<DataArray<T>&>(*(search->second));
    }

    template<typename T> DataArray<T>* GetPointer(const std::string& name) const {
        auto search = m_data.find(name);
        if (search == m_data.end())
            return nullptr;
        return &dynamic_cast<DataArray<T>&>(*(search->second));
    }

private:
    int                                                             m_count;
    std::unordered_map<std::string, std::unique_ptr<DataArrayBase>> m_data;
};

#endif   // HYBRIDMPM_DS_H
