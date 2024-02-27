//
// Created by 王晨辉 on 2024/2/1.
//

#ifndef HYBRIDMPM_DATAARRAY_H
#define HYBRIDMPM_DATAARRAY_H


#include "DataArrayBase.h"

namespace DATA {
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

template<typename Type, bool IsConst> class DataArrayIterator;

template<typename Type> class DataArray : public DataArrayBase {
public:
    using Base = DataArrayBase;
    using Base::ranges;
    using Base::name;


    std::vector<Type> array;

    DataArray(const std::string& name, const DisjointRanges& ranges, std::vector<Type>&& array)
        : DataArrayBase(name, ranges)
        , array(std::move(array)) {
        assert(ranges.Length() == (int)array.size());
    }

    ~DataArray() override {}
    void Clear() override {
        ranges.mRanges.clear();
        array.clear();
    }
    size_t Size() const override { return array.size(); }

    Type& operator[](size_t i) {
        assert(i < array.size());
        return array[i];
    }

    const Type& operator[](size_t i) const {
        assert(i < array.size());
        return array[i];
    }

    const Type* GetValue(int entryId) const {
        int valueId = ValueId(entryId);
        if (valueId < 0) {
            return nullptr;
        } else {
            return &(array[valueId]);
        }
    }

    const Type* GetValue(int entryId) {
        int valueId = ValueId(entryId);
        if (valueId < 0) {
            return nullptr;
        } else {
            return &(array[valueId]);
        }
    }

    DataArrayIterator<Type, false> Iter() { return DataArrayIterator<Type, false>(*this, ranges); }

    DataArrayIterator<Type, true> Iter() const {
        return DataArrayIterator<Type, true>(*this, ranges);
    }

    DataArrayIterator<Type, false> SubsetIter(const DisjointRanges& dr) {
        return DataArrayIterator<Type, false>(*this, dr);
    }

    DataArrayIterator<Type, true> SubsetIter(const DisjointRanges& dr) const {
        return DataArrayIterator<Type, true>(*this, dr);
    }
};

template<typename Type, bool IsConst> class DataArrayIterator {
private:
    using IterT = std::conditional_t<IsConst, typename std::vector<Type>::const_iterator,
                                     typename std::vector<Type>::iterator>;

    // Iterator into ranges
    typename DisjointRanges::ConstIterator r;

    // Iterator into subset
    typename DisjointRanges::ConstIterator s;

    // Iterator into data array
    IterT a;

    const typename DisjointRanges::ConstIterator end;

    // Current entry id
    int p;

public:
    using BatchType     = std::conditional_t<IsConst, const DataArray<Type>&, DataArray<Type>&>;
    using ReferenceType = std::conditional_t<IsConst, const Type&, Type&>;

    DataArrayIterator<Type, IsConst>(BatchType batch, const DisjointRanges& subset)
        : r(batch.ranges.begin())
        , s(subset.begin())
        , a(batch.array.begin())
        , end(subset.end())
        , p((r != batch.ranges.end()) ? (r->lower) : -1) {}

    DataArrayIterator<Type, IsConst>(BatchType batch)
        : DataArrayIterator<Type, IsConst>(batch, batch.ranges) {}

    // check if the iter is valid
    explicit operator bool() const {return s != end;}

    bool operator==(const DataArrayIterator& o) const { return p == o.p; }

    bool operator!=(const DataArrayIterator& o) const { return p != o.p; }

    int EntryId() const {return p;}


    DataArrayIterator<Type, IsConst>& operator++() {
        a++;
        p++;
        if(p == s->upper){
            s++;
            if(s != end){
                AdvanceToEntryId(s->lower);
            }
        }
        return *this;
    }

    DataArrayIterator<Type, IsConst> operator++(int) {
        DataArrayIterator<Type, IsConst> temp(*this);
        operator++();
        return temp;
    }


    void AdvanceToEntryId(int eid){
        while(r->upper <= eid){
            a += r->upper - p;
            r++;
            p = r->lower;
        }
        if(p < eid) {
            a += eid - p;
            p = eid;
        }
    }

    ReferenceType operator*() const {
        return *a;
    }
};
}   // namespace DATA

using DataArrayBase = DATA::DataArrayBase;
template<typename Type> using DataArray = DATA::DataArray<Type>;

#endif   // HYBRIDMPM_DATAARRAY_H
