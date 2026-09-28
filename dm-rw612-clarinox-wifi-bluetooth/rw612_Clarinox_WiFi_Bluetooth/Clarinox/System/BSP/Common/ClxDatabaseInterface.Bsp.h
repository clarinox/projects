#ifndef ClxDatabaseInterface_Bsp_h
#define ClxDatabaseInterface_Bsp_h

/*******************************************************************************
*
* Project             Clarinox SoftFrame
* File                ClxDatabaseInterface.Bsp.h
* Description         Declares ClarinoxBlue Database Storage Interface
*
* This software is copyrighted and contains proprietary information of 
* Clarinox Technologies Proprietary Limited. 
* Copying or reproduction without prior written approval is prohibited.
*
* All rights reserved. Copyright (c) 2001-2026 by Clarinox Technologies Pty. Ltd.
*
*******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif


/**
Handle to a record that exists in an open database. The handle object will be valid until the record is deleted from the database, or the database is closed.
*/
typedef void* ClxDatabaseRecordHandle;


/**
ClxDatabaseInterface is an interface to the database architecture available in the platform. The interface is implemented as part of the BSP architecture.

A database is supposed to be under the control of one entity only (which is the owner of
the database object). The database shall not be modified by any other entity.

NOTE : An implementation of this interface may be NOT thread-safe.

NOTE : Only one instance of this object shall exist at any time for a single database.

The database object may contain zero or more data records.

NOTE : A database is an unordered list of records. The order of records in the database is of no significance.
Therefore, the user shall NOT make any assumption about the order of the records.

A record is accessed via its handle, of type ClxDatabaseRecordHandle. The handle will be valid until the record is deleted, or the database is closed.

A record may have one or more fields. Fields are data elements which are defined for a data record. Each field consists of a null-terminated UTF8 name,
type (e.g. Integer, Boolean, String, Binary Data, ...), and the value. Fields are represented by objects of type ClxConfigParam.  

NOTE : Two fields in the same record cannot have the same name. Field names are case sensitive.

The interface contains methods to create and delete database records, get the handle of a record from its index in the database, and read and write
fields of a record.

NOTE : All methods of this interface SHALL be implemented.
*/
struct ClxDatabaseInterface
{
    /**
    Creates a new blank record in the database. If successful, the handle to the new record will be returned.
    The handle can then be used to add fields to the record, by a call to #writeRecordFields method.

    \param[ in ] this_ Pointer to the this object.
    \param[ out ] recordHandle If successful (e.g. the function returns CLX_SUCCESS), this argument will contain the handle to the new record.
                               If not successful, this argument shall be ignored.

    \return CLX_SUCCESS if successful.
    Any other value indicates an error.
    */
    ClxResult (*createRecord) (_in_ struct ClxDatabaseInterface* this_,
                               _out_ ClxDatabaseRecordHandle* recordHandle);

    /**
    Deletes a record, and all of its fields, from the database.

    NOTE : If successful, the handle to the record will be invalid and shall not be used any more.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] recordHandle Handle to the record to be deleted.

    \return CLX_SUCCESS if successful.
    Any other value indicates an error.
    */
    ClxResult (*deleteRecord) (_in_ struct ClxDatabaseInterface* this_,
                               _in_ ClxDatabaseRecordHandle recordHandle);


    /**
    Returns the handle to a record from its zero-based index. This method can be used to iterate all records.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] recordIndex The zero-based index if the record to which the handle to be returned.

    \return If successful, the handle to the record.
    NULL otherwise.
    */
    ClxDatabaseRecordHandle (*getRecordHandle) (_in_ struct ClxDatabaseInterface* this_,
                                                _in_ u4 recordIndex);

    /**
    Returns the number of records in the database.

    \param[ in ] this_ Pointer to the this object.

    \return The current number of records in the database.
    */
    ClxSize (*getNumberOfRecords) (_in_ struct ClxDatabaseInterface* this_);

    /**
    Reads one or more fields of a record.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] recordHandle Handle to the record.
    \param[ in ] fields List of the fields to which the values are to be returned.
                        If successful, the paramInfo.processed member of each successfully-read field will be set to TRUE.

    \return CLX_SUCCESS if successful.
    Any other value indicates an error.
    */
    ClxResult (*readRecordFields) (_in_ struct ClxDatabaseInterface* this_,
                                   _in_ ClxDatabaseRecordHandle recordHandle,
                                   _out_ ClxConfigList* fields);

    /**
    Writes one or more fields to a record. Before the new fields are applied, all the old fields of the record SHALL be removed.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] recordHandle Handle to the record.
    \param[ in ] fields List of the fields to which the values are to be written.
                        If successful, the paramInfo.processed member of each successfully-written field will be set to TRUE.
    
    \return CLX_SUCCESS if successful.
    Any other value indicates an error.
    */
    ClxResult (*writeRecordFields) (_in_ struct ClxDatabaseInterface* this_,
                                    _in_ ClxDatabaseRecordHandle recordHandle,
                                    _in_ ClxConfigList* fields);

    /**
    Searches all records in the database for the provided field. If a record with the provided field name, and field type exists, the handle to it will be returned.
    If no record with the provided field is found, this function will return NULL.

    IMPORTANT : The value of the field object provided SHALL be ignored. The search shall be based on the field name, and the field type only.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] field The field to search for in all records in the database. Only the field name (field->paramName), and field type (field->paramTypeID) are of importance.
                       The other members of field object SHALL be ignored.
    
    \return CLX_SUCCESS if successful.
    Any other value indicates an error.
    */
    ClxDatabaseRecordHandle (*findRecordByField) (_in_ struct ClxDatabaseInterface* this_,
                                                  _in_ const ClxConfigParam* field);
};


/**
Database manager. It is responsible for opening and closing databases and returning valid ClxDatabaseInterface object for an open database.
*/
struct ClxDatabaseManager
{
    /**
    Opens a database. The database SHALL already exist. Otherwise, the implementation SHALL return an error.

    IMPORTANT : If the function returns CLX_SUCCESS, the second argument (databaseName) SHALL not be deleted or modified until the database is closed.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] databaseName The name of the database. 
    \param[ out ] database If successful (e.g. the function returns CLX_SUCCESS), this argument will contain a pointer to the database.
                               If not successful, this argument shall be ignored.

    \return CLX_SUCCESS if successful.
    Any other value indicates an error.    
    */
    ClxResult (*openDatabase) (_in_ struct ClxDatabaseManager* this_,
                               _user_in_ const s1* databaseName,
                               _out_ struct ClxDatabaseInterface** database);

    /**
    Closes an open database. An implementation cannot fail.

    \param[ in ] this_ Pointer to the this object.
    \param[ in ] database The database to close. As soon as this function returns, the database object will be invalid and SHALL not be used any more.
    */
    void (*closeDatabase) (_in_ struct ClxDatabaseManager* this_,
                           _in_ struct ClxDatabaseInterface* database);
};



/**
Database manager for ClarinoxSoftFrame. An implementation (of type ClxDatabaseManager) is responsible for managing
the database(s) used to store information of Clarinox stacks (e.g. such as Bluetooth pairing information, ...) in the persistent storage. 
A user-defined implementation is optional. If not provided, an internal default implementation will be used. 
The default implementation will make use of the file system BSP interface (clxFileBspInterface)
in order to write the paired information into a database file and read the information back.
*/
extern struct ClxDatabaseManager* clxBspSoftFrameDatabaseManager;


#ifdef __cplusplus
}
#endif


#endif // ClxDatabaseInterface_Bsp_h
