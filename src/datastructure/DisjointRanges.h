//
// Created by 王晨辉 on 2024/2/1.
//

#ifndef HYBRIDMPM_DISJOINTRANGES_H
#define HYBRIDMPM_DISJOINTRANGES_H


#include <iostream>
#include <vector>
#include <util/Log.h>


/*
 * [lower, upper)
 */
struct Range {
    int lower;
    int upper;

    Range() = default;

    Range(int lower, int upper)
        : lower(lower)
        , upper(upper) {}

    Range(const Range& range)            = default;
    Range(Range&& range)                 = default;
    Range& operator=(const Range& range) = default;
    Range& operator=(Range&& range)      = default;

    bool operator==(const Range& range) const {
        return (lower == range.lower) && (upper == range.upper);
    }

    int Length() const { return upper - lower; }

    std::string ToString() const{
        std::string ret;
        ret += ("[" + std::to_string(lower) + ", " + std::to_string(upper) + ")");
        return ret;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Range& m) {
    return os << "[" << m.lower << ", " << m.upper << ")";
}

class DisjointRanges {
public:
    using ConstIterator = std::vector<Range>::const_iterator;
    using Iterator      = std::vector<Range>::iterator;

    DisjointRanges(int grainSize = 7)
        : mGrainSize(grainSize) {}

    DisjointRanges(std::initializer_list<Range> l, int grainSize = 7)
        : mGrainSize(grainSize) {
        for (auto r : l) {
            Append(r);
        }
    }

    void Append(const Range& range) {
        MPM_ASSERT(mRanges.empty() || range.lower >= mRanges.back().upper,
                   "New ranges must come after old ones");
        if (!mRanges.empty() && range.lower == mRanges.back().upper) {
            mRanges.back().upper = range.upper;
        } else {
            mRanges.push_back(range);
        }
    }

    void Append(int lower, int upper) { Append(Range{lower, upper}); }

    int Length() const {
        int l = 0;
        for (auto r : mRanges) {
            l += (r.upper - r.lower);
        }
        return l;
    }

    // used for c++ range expression.
    Iterator begin(){return mRanges.begin();}
    Iterator end(){return mRanges.end();}
    ConstIterator begin() const {return mRanges.cbegin();}
    ConstIterator end() const {return mRanges.cend();}

    Range& operator[](size_t i){
        return mRanges[i];
    }

    bool Empty() const {return Length() == 0;}

    size_t Size() const{
        return mRanges.size();
    }

    bool operator==(const DisjointRanges& other) const{
        return mRanges == other.mRanges;
    }

    bool Valid() const {
        int lastUpper = -1;
        for(const auto& range : mRanges){
            if(lastUpper >= range.lower) return false;
            if(range.upper >= range.lower) return false;
        }
        return true;
    }

    std::string ToString() const {
        std::string ret;
        for(const auto& range: mRanges){
            ret += (range.ToString() + " ");
        }
    }

public:
    int                mGrainSize;
    std::vector<Range> mRanges;
};

#endif   // HYBRIDMPM_DISJOINTRANGES_H
