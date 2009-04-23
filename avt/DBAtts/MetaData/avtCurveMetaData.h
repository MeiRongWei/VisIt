/*****************************************************************************
*
* Copyright (c) 2000 - 2008, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-400142
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

#ifndef AVTCURVEMETADATA_H
#define AVTCURVEMETADATA_H
#include <dbatts_exports.h>
#include <string>
#include <AttributeSubject.h>

// ****************************************************************************
// Class: avtCurveMetaData
//
// Purpose:
//    Contains curve metadata attributes
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class DBATTS_API avtCurveMetaData : public AttributeSubject
{
public:
    avtCurveMetaData();
    avtCurveMetaData(const avtCurveMetaData &obj);
    virtual ~avtCurveMetaData();

    virtual avtCurveMetaData& operator = (const avtCurveMetaData &obj);
    virtual bool operator == (const avtCurveMetaData &obj) const;
    virtual bool operator != (const avtCurveMetaData &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();

    // User-defined methods
    avtCurveMetaData(const std::string &n);
    avtCurveMetaData(const std::string &n, double minS, double maxS, double minE, double maxE);
    void SetSpatialExtents(const double *);
    void UnsetSpatialExtents();
    void SetDataExtents(const double *);
    void UnsetDataExtents();
    void Print(ostream &, int = 0) const;

    // IDs that can be used to identify fields in case statements
    enum {
        ID_name = 0,
        ID_originalName,
        ID_validVariable,
        ID_xUnits,
        ID_xLabel,
        ID_yUnits,
        ID_yLabel,
        ID_hasSpatialExtents,
        ID_minSpatialExtents,
        ID_maxSpatialExtents,
        ID_hasDataExtents,
        ID_minDataExtents,
        ID_maxDataExtents,
        ID_hideFromGUI,
        ID_from1DScalarName
    };

public:
    std::string  name;
    std::string  originalName;
    bool         validVariable;
    std::string  xUnits;
    std::string  xLabel;
    std::string  yUnits;
    std::string  yLabel;
    bool         hasSpatialExtents;
    double       minSpatialExtents;
    double       maxSpatialExtents;
    bool         hasDataExtents;
    double       minDataExtents;
    double       maxDataExtents;
    bool         hideFromGUI;
    std::string from1DScalarName;

private:
    // Static class format string for type map.
    static const char *TypeMapFormatString;
};

#endif
