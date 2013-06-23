// ***************************************************************************
//
// Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
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

import java.util.Vector;

// ****************************************************************************
// Class: ViewerClientInformation
//
// Purpose:
//    This class contains information generated for each client
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class ViewerClientInformation extends AttributeSubject
{
    private static int ViewerClientInformation_numAdditionalAtts = 2;

    // Enum values
    public final static int OUTPUTFORMAT_NONE = 0;
    public final static int OUTPUTFORMAT_IMAGE = 1;
    public final static int OUTPUTFORMAT_BMP = 2;
    public final static int OUTPUTFORMAT_PNG = 3;
    public final static int OUTPUTFORMAT_JPEG = 4;
    public final static int OUTPUTFORMAT_DATA = 5;
    public final static int OUTPUTFORMAT_VTK = 6;
    public final static int OUTPUTFORMAT_X3D = 7;
    public final static int OUTPUTFORMAT_USERDATA = 8;
    public final static int OUTPUTFORMAT_JSON = 9;
    public final static int OUTPUTFORMAT_MESSAGE = 10;


    public ViewerClientInformation()
    {
        super(ViewerClientInformation_numAdditionalAtts);

        vars = new Vector();
        supportedFormats = new Vector();
        supportedFormats.addElement(new String("None"));
        supportedFormats.addElement(new String("Image"));
        supportedFormats.addElement(new String("BMP"));
        supportedFormats.addElement(new String("PNG"));
        supportedFormats.addElement(new String("JPEG"));
        supportedFormats.addElement(new String("Data"));
        supportedFormats.addElement(new String("VTK"));
        supportedFormats.addElement(new String("X3D"));
        supportedFormats.addElement(new String("UserData"));
        supportedFormats.addElement(new String("JSON"));
        supportedFormats.addElement(new String("Message"));
    }

    public ViewerClientInformation(int nMoreFields)
    {
        super(ViewerClientInformation_numAdditionalAtts + nMoreFields);

        vars = new Vector();
        supportedFormats = new Vector();
        supportedFormats.addElement(new String("None"));
        supportedFormats.addElement(new String("Image"));
        supportedFormats.addElement(new String("BMP"));
        supportedFormats.addElement(new String("PNG"));
        supportedFormats.addElement(new String("JPEG"));
        supportedFormats.addElement(new String("Data"));
        supportedFormats.addElement(new String("VTK"));
        supportedFormats.addElement(new String("X3D"));
        supportedFormats.addElement(new String("UserData"));
        supportedFormats.addElement(new String("JSON"));
        supportedFormats.addElement(new String("Message"));
    }

    public ViewerClientInformation(ViewerClientInformation obj)
    {
        super(ViewerClientInformation_numAdditionalAtts);

        int i;

        // *** Copy the vars field ***
        vars = new Vector(obj.vars.size());
        for(i = 0; i < obj.vars.size(); ++i)
        {
            ViewerClientInformationElement oldObj = (ViewerClientInformationElement)obj.vars.elementAt(i);
            vars.addElement(new ViewerClientInformationElement(oldObj));
        }

        supportedFormats = new Vector(obj.supportedFormats.size());
        for(i = 0; i < obj.supportedFormats.size(); ++i)
            supportedFormats.addElement(new String((String)obj.supportedFormats.elementAt(i)));


        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return ViewerClientInformation_numAdditionalAtts;
    }

    public boolean equals(ViewerClientInformation obj)
    {
        int i;

        // Compare the elements in the vars vector.
        boolean vars_equal = (obj.vars.size() == vars.size());
        for(i = 0; (i < vars.size()) && vars_equal; ++i)
        {
            // Make references to ViewerClientInformationElement from Object.
            ViewerClientInformationElement vars1 = (ViewerClientInformationElement)vars.elementAt(i);
            ViewerClientInformationElement vars2 = (ViewerClientInformationElement)obj.vars.elementAt(i);
            vars_equal = vars1.equals(vars2);
        }
        // Compare the elements in the supportedFormats vector.
        boolean supportedFormats_equal = (obj.supportedFormats.size() == supportedFormats.size());
        for(i = 0; (i < supportedFormats.size()) && supportedFormats_equal; ++i)
        {
            // Make references to String from Object.
            String supportedFormats1 = (String)supportedFormats.elementAt(i);
            String supportedFormats2 = (String)obj.supportedFormats.elementAt(i);
            supportedFormats_equal = supportedFormats1.equals(supportedFormats2);
        }
        // Create the return value
        return (vars_equal &&
                supportedFormats_equal);
    }

    // Property setting methods
    public void SetSupportedFormats(Vector supportedFormats_)
    {
        supportedFormats = supportedFormats_;
        Select(1);
    }

    // Property getting methods
    public Vector GetVars() { return vars; }
    public Vector GetSupportedFormats() { return supportedFormats; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
        {
            buf.WriteInt(vars.size());
            for(int i = 0; i < vars.size(); ++i)
            {
                ViewerClientInformationElement tmp = (ViewerClientInformationElement)vars.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(1, buf))
            buf.WriteStringVector(supportedFormats);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            {
                int len = buf.ReadInt();
                vars.clear();
                for(int j = 0; j < len; ++j)
                {
                    ViewerClientInformationElement tmp = new ViewerClientInformationElement();
                    tmp.Read(buf);
                    vars.addElement(tmp);
                }
            }
            Select(0);
            break;
        case 1:
            SetSupportedFormats(buf.ReadStringVector());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "vars = {\n";
        for(int i = 0; i < vars.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)vars.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < vars.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        str = str + stringVectorToString("supportedFormats", supportedFormats, indent) + "\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddVars(ViewerClientInformationElement obj)
    {
        vars.addElement(new ViewerClientInformationElement(obj));
        Select(0);
    }

    public void ClearVars()
    {
        vars.clear();
        Select(0);
    }

    public void RemoveVars(int index)
    {
        if(index >= 0 && index < vars.size())
        {
            vars.remove(index);
            Select(0);
        }
    }

    public int GetNumVars()
    {
        return vars.size();
    }

    public ViewerClientInformationElement GetVars(int i)
    {
        ViewerClientInformationElement tmp = (ViewerClientInformationElement)vars.elementAt(i);
        return tmp;
    }


    // Attributes
    private Vector vars; // vector of ViewerClientInformationElement objects
    private Vector supportedFormats; // vector of String objects
}

