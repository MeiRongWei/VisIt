/*****************************************************************************
*
* Copyright (c) 2000 - 2013, Lawrence Livermore National Security, LLC
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
//                            avtALSFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_ALS_FILE_FORMAT_H
#define AVT_ALS_FILE_FORMAT_H

#include <avtSTMDFileFormat.h>

#include <vector>
#include <hdf5.h>

// ****************************************************************************
//  Class: avtALSFileFormat
//
//  Purpose:
//      Reads in ALS files as a plugin to VisIt.
//
//  Programmer: hari -- generated by xml2avt
//  Creation:   Mon Apr 14 16:36:42 PST 2014
//
// ****************************************************************************

class avtALSFileFormat : public avtSTMDFileFormat
{
  public:
                       avtALSFileFormat(const char *);
    virtual           ~avtALSFileFormat() {;}

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, int domain,
    //                                     const char *type, void *args, 
    //                                     DestructorFunction &);
    //

    //
    // If you know the cycle number, overload this function.
    // Otherwise, VisIt will make up a reasonable one for you.
    //
    // virtual int         GetCycle(void);
    //

    virtual const char    *GetType(void)   { return "ALS"; }
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

    void SetGroupName(const std::string& name) { m_groupName = name; }

  protected:
    enum ALSDataType {STANDARD, TOMO, OTHER};

    ALSDataType		   m_dataType;
    // DATA MEMBERS
    std::string            m_filename;
    size_t                 m_width, m_height, m_slices;
    std::string            m_groupName;
    bool                   m_initialized;
    std::vector<std::string> m_datasetNames;
    int                    m_ver;
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *);

  private:
    void Initialize();
    bool InitializeHeader();
    bool InitializeStandardHeader(hid_t file);
    bool InitializeTomoHeader(hid_t file);
    vtkDataArray* GetDataSet();
    vtkDataArray* GetTomoDataSet(hid_t file);
    vtkDataArray* GetStandardDataSet(hid_t file);
};


#endif
