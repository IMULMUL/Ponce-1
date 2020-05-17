//! \file
/*
**  Copyright (c) 2016 - Ponce
**  Authors:
**         Alberto Garcia Illera        agarciaillera@gmail.com
**         Francisco Oca                francisco.oca.gonzalez@gmail.com
**
**  This program is under the terms of the BSD License.
*/

#pragma once
#include <vector>
#include "kernwin.hpp"


// column widths
struct ponce_table_chooser_t : public chooser_multi_t
{
protected:
    static const int widths_[];
    static const char* header_[];
    typedef struct s
    {
        triton::usize id = 0;
        triton::uint64 address = 0;
        std::string register_name;
        triton::uint512 value = 0;
        std::string comment;
        std::string var_name;
    }list_item_t;
   
    
public:
    

    virtual ~ponce_table_chooser_t() {
        if (!table_item_list.empty()) {
            table_item_list.clear();
        }
    }
    // function that returns number of lines in the list
    virtual size_t idaapi get_count() const { return table_item_list.size(); }

    // function that generates the list line
    virtual void idaapi get_row(qstrvec_t* cols, int* icon_,
        chooser_item_attrs_t* attrs,
        size_t n) const;

    // function that is called when the user wants to refresh the chooser
    virtual cbres_t idaapi refresh(sizevec_t* sel) {
        fill_entryList();
        //return adjust_last_item(n);  // try to preserve the cursor
        return ALL_CHANGED;
    }

    // function that is called when the user wants to close the chooser
    virtual cbres_t idaapi destroy(ssize_t n) {
        if (!table_item_list.empty()) {
            table_item_list.clear();
        }
        // return adjust_last_item(n);  // try to preserve the cursor
        return ALL_CHANGED;
    }

    virtual cbres_t idaapi enter(sizevec_t* sel);
    virtual void select(const sizevec_t& sel) const;
public:
    std::vector<list_item_t> table_item_list;

    ponce_table_chooser_t();
    void fill_entryList();
};



#ifndef __IDA70__

// column widths
static const int widths[] = { CHCOL_DEC | 8,
CHCOL_HEX,
5,
16,
6,
6,
16 };

// column headers
static const char* header[] =
{
    "Id",
    "Address",
    "Reg Name",
    "Value",
    "Is Tainted",
    "Comment",
};
#endif
