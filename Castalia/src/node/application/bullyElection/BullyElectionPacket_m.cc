//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/application/bullyElection/BullyElectionPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BullyElectionPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

BullyElectionData::BullyElectionData()
{
    nodeID = 0;
    locX = 0;
    locY = 0;
}

void doPacking(cCommBuffer *b, BullyElectionData& a)
{
    doPacking(b,a.nodeID);
    doPacking(b,a.locX);
    doPacking(b,a.locY);
}

void doUnpacking(cCommBuffer *b, BullyElectionData& a)
{
    doUnpacking(b,a.nodeID);
    doUnpacking(b,a.locX);
    doUnpacking(b,a.locY);
}

class BullyElectionDataDescriptor : public cClassDescriptor
{
  public:
    BullyElectionDataDescriptor();
    virtual ~BullyElectionDataDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BullyElectionDataDescriptor);

BullyElectionDataDescriptor::BullyElectionDataDescriptor() : cClassDescriptor("BullyElectionData", "")
{
}

BullyElectionDataDescriptor::~BullyElectionDataDescriptor()
{
}

bool BullyElectionDataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BullyElectionData *>(obj)!=NULL;
}

const char *BullyElectionDataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BullyElectionDataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int BullyElectionDataDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *BullyElectionDataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeID",
        "locX",
        "locY",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int BullyElectionDataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "locX")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "locY")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BullyElectionDataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "double",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *BullyElectionDataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int BullyElectionDataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionData *pp = (BullyElectionData *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BullyElectionDataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionData *pp = (BullyElectionData *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->nodeID);
        case 1: return double2string(pp->locX);
        case 2: return double2string(pp->locY);
        default: return "";
    }
}

bool BullyElectionDataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionData *pp = (BullyElectionData *)object; (void)pp;
    switch (field) {
        case 0: pp->nodeID = string2ulong(value); return true;
        case 1: pp->locX = string2double(value); return true;
        case 2: pp->locY = string2double(value); return true;
        default: return false;
    }
}

const char *BullyElectionDataDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *BullyElectionDataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionData *pp = (BullyElectionData *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(BullyElectionDataPacket);

BullyElectionDataPacket::BullyElectionDataPacket(const char *name, int kind) : ::ApplicationPacket(name,kind)
{
}

BullyElectionDataPacket::BullyElectionDataPacket(const BullyElectionDataPacket& other) : ::ApplicationPacket(other)
{
    copy(other);
}

BullyElectionDataPacket::~BullyElectionDataPacket()
{
}

BullyElectionDataPacket& BullyElectionDataPacket::operator=(const BullyElectionDataPacket& other)
{
    if (this==&other) return *this;
    ::ApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void BullyElectionDataPacket::copy(const BullyElectionDataPacket& other)
{
    this->extraData_var = other.extraData_var;
}

void BullyElectionDataPacket::parsimPack(cCommBuffer *b)
{
    ::ApplicationPacket::parsimPack(b);
    doPacking(b,this->extraData_var);
}

void BullyElectionDataPacket::parsimUnpack(cCommBuffer *b)
{
    ::ApplicationPacket::parsimUnpack(b);
    doUnpacking(b,this->extraData_var);
}

BullyElectionData& BullyElectionDataPacket::getExtraData()
{
    return extraData_var;
}

void BullyElectionDataPacket::setExtraData(const BullyElectionData& extraData)
{
    this->extraData_var = extraData;
}

class BullyElectionDataPacketDescriptor : public cClassDescriptor
{
  public:
    BullyElectionDataPacketDescriptor();
    virtual ~BullyElectionDataPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BullyElectionDataPacketDescriptor);

BullyElectionDataPacketDescriptor::BullyElectionDataPacketDescriptor() : cClassDescriptor("BullyElectionDataPacket", "ApplicationPacket")
{
}

BullyElectionDataPacketDescriptor::~BullyElectionDataPacketDescriptor()
{
}

bool BullyElectionDataPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BullyElectionDataPacket *>(obj)!=NULL;
}

const char *BullyElectionDataPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BullyElectionDataPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int BullyElectionDataPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *BullyElectionDataPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "extraData",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int BullyElectionDataPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "extraData")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BullyElectionDataPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "BullyElectionData",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *BullyElectionDataPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int BullyElectionDataPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionDataPacket *pp = (BullyElectionDataPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BullyElectionDataPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionDataPacket *pp = (BullyElectionDataPacket *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getExtraData(); return out.str();}
        default: return "";
    }
}

bool BullyElectionDataPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionDataPacket *pp = (BullyElectionDataPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BullyElectionDataPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(BullyElectionData));
        default: return NULL;
    };
}

void *BullyElectionDataPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BullyElectionDataPacket *pp = (BullyElectionDataPacket *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getExtraData()); break;
        default: return NULL;
    }
}


