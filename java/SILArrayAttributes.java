// ***************************************************************************
//
// Copyright (c) 2000 - 2008, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-400142
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit;


// ****************************************************************************
// Class: SILArrayAttributes
//
// Purpose:
//    This class contain the information needed to represent a SIL Array.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   Tue Jan 15 13:53:53 PST 2008
//
// Modifications:
//   
// ****************************************************************************

public class SILArrayAttributes extends AttributeSubject
{
    public SILArrayAttributes()
    {
        super(9);

        prefix = new String("");
        numSets = 0;
        firstSetName = 0;
        useUniqueIDs = false;
        firstSet = 0;
        colIndex = 0;
        category = new String("");
        role = 0;
        colParent = 0;
    }

    public SILArrayAttributes(SILArrayAttributes obj)
    {
        super(9);

        prefix = new String(obj.prefix);
        numSets = obj.numSets;
        firstSetName = obj.firstSetName;
        useUniqueIDs = obj.useUniqueIDs;
        firstSet = obj.firstSet;
        colIndex = obj.colIndex;
        category = new String(obj.category);
        role = obj.role;
        colParent = obj.colParent;

        SelectAll();
    }

    public boolean equals(SILArrayAttributes obj)
    {
        // Create the return value
        return ((prefix == obj.prefix) &&
                (numSets == obj.numSets) &&
                (firstSetName == obj.firstSetName) &&
                (useUniqueIDs == obj.useUniqueIDs) &&
                (firstSet == obj.firstSet) &&
                (colIndex == obj.colIndex) &&
                (category == obj.category) &&
                (role == obj.role) &&
                (colParent == obj.colParent));
    }

    // Property setting methods
    public void SetPrefix(String prefix_)
    {
        prefix = prefix_;
        Select(0);
    }

    public void SetNumSets(int numSets_)
    {
        numSets = numSets_;
        Select(1);
    }

    public void SetFirstSetName(int firstSetName_)
    {
        firstSetName = firstSetName_;
        Select(2);
    }

    public void SetUseUniqueIDs(boolean useUniqueIDs_)
    {
        useUniqueIDs = useUniqueIDs_;
        Select(3);
    }

    public void SetFirstSet(int firstSet_)
    {
        firstSet = firstSet_;
        Select(4);
    }

    public void SetColIndex(int colIndex_)
    {
        colIndex = colIndex_;
        Select(5);
    }

    public void SetCategory(String category_)
    {
        category = category_;
        Select(6);
    }

    public void SetRole(int role_)
    {
        role = role_;
        Select(7);
    }

    public void SetColParent(int colParent_)
    {
        colParent = colParent_;
        Select(8);
    }

    // Property getting methods
    public String  GetPrefix() { return prefix; }
    public int     GetNumSets() { return numSets; }
    public int     GetFirstSetName() { return firstSetName; }
    public boolean GetUseUniqueIDs() { return useUniqueIDs; }
    public int     GetFirstSet() { return firstSet; }
    public int     GetColIndex() { return colIndex; }
    public String  GetCategory() { return category; }
    public int     GetRole() { return role; }
    public int     GetColParent() { return colParent; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteString(prefix);
        if(WriteSelect(1, buf))
            buf.WriteInt(numSets);
        if(WriteSelect(2, buf))
            buf.WriteInt(firstSetName);
        if(WriteSelect(3, buf))
            buf.WriteBool(useUniqueIDs);
        if(WriteSelect(4, buf))
            buf.WriteInt(firstSet);
        if(WriteSelect(5, buf))
            buf.WriteInt(colIndex);
        if(WriteSelect(6, buf))
            buf.WriteString(category);
        if(WriteSelect(7, buf))
            buf.WriteInt(role);
        if(WriteSelect(8, buf))
            buf.WriteInt(colParent);
    }

    public void ReadAtts(int n, CommunicationBuffer buf)
    {
        for(int i = 0; i < n; ++i)
        {
            int index = (int)buf.ReadByte();
            switch(index)
            {
            case 0:
                SetPrefix(buf.ReadString());
                break;
            case 1:
                SetNumSets(buf.ReadInt());
                break;
            case 2:
                SetFirstSetName(buf.ReadInt());
                break;
            case 3:
                SetUseUniqueIDs(buf.ReadBool());
                break;
            case 4:
                SetFirstSet(buf.ReadInt());
                break;
            case 5:
                SetColIndex(buf.ReadInt());
                break;
            case 6:
                SetCategory(buf.ReadString());
                break;
            case 7:
                SetRole(buf.ReadInt());
                break;
            case 8:
                SetColParent(buf.ReadInt());
                break;
            }
        }
    }


    // Attributes
    private String  prefix;
    private int     numSets;
    private int     firstSetName;
    private boolean useUniqueIDs;
    private int     firstSet;
    private int     colIndex;
    private String  category;
    private int     role;
    private int     colParent;
}

