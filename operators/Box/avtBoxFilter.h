/*****************************************************************************
*
* Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//  File: avtBoxFilter.h
// ************************************************************************* //

#ifndef AVT_Box_FILTER_H
#define AVT_Box_FILTER_H

#include <avtPluginDataTreeIterator.h>

#include <BoxAttributes.h>

class vtkDataSet;
class vtkRectilinearGrid;
class vtkUnstructuredGrid;


// ****************************************************************************
//  Class: avtBoxFilter
//
//  Purpose:
//      A plugin operator for Box.
//
//  Programmer: childs -- generated by xml2info
//  Creation:   Mon Nov 12 16:57:31 PST 2001
//
//  Modifications:
//
//    Mark C. Miller, Tue Sep 28 19:57:42 PDT 2004
//    Added selection id and ModifyContract implementation
//
//    Hank Childs, Sun Apr 24 11:11:46 PDT 2005
//    Add special support for rectilinear grids. ['6155]
//
//    Kathleen Bonnell, Mon Mar 23 18:26:59 PDT 2009
//    Made this derive again from avtPluginDataTreeIterator instead of
//    avtSIMODataTreeIterator.
// 
//    Eric Brugger, Tue Jul 22 17:07:12 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtBoxFilter : public avtPluginDataTreeIterator
{
  public:
                         avtBoxFilter();
    virtual             ~avtBoxFilter();

    static avtFilter    *Create();

    virtual const char  *GetType(void)  { return "avtBoxFilter"; };
    virtual const char  *GetDescription(void)
                             { return "Finding cells within a box"; };

    virtual void         SetAtts(const AttributeGroup*);
    virtual bool         Equivalent(const AttributeGroup*);

  protected:
    BoxAttributes   atts;
    int             selID;

    virtual avtDataRepresentation *ExecuteData(avtDataRepresentation *);
    vtkRectilinearGrid    *RectilinearExecute(vtkRectilinearGrid *);
    vtkUnstructuredGrid   *GeneralExecute(vtkDataSet *);
    virtual void           UpdateDataObjectInfo(void);
    virtual avtContract_p  ModifyContract(avtContract_p);
    vtkRectilinearGrid    *CurveExecute(vtkRectilinearGrid *);

};


#endif
