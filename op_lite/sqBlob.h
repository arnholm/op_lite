#ifndef SQBLOB_H
#define SQBLOB_H

/*
** Author: Carsten Arnholm, January 2010
** This code was written for my weather station project
**
** This code follows the sqlite3 license model, i.e.:
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
*/

#include "op_lite_config.h"

#include <vector>
using namespace std;

/// low level: sqBlob represents a binary large object
class OP_LITE_PUBLIC sqBlob {
   friend class sqStatement;
   friend class sqTable;

public:
   /// default constructor
   sqBlob();

   /// copy constructor
   /*!  \param  other  other blob to assign data from */
   sqBlob(const sqBlob& other);

   /// assignment operator
   /*!  \param  other  other blob to assign data from
        \return this blob */
   sqBlob& operator=(const sqBlob& other);

   /// Destructor
   virtual ~sqBlob();

   /// return the uncompressed size of the user data in bytes
   /*! \return uncompressed size of the user data in bytes  */
   size_t size_bytes() const;

   /// return the uncompressed size of the user data in T units
   /*! \return uncompressed size of the user data in T units  */
   template <typename T>
   size_t usize() const;

   /// return size of data in database [bytes] (Note: header included)
   /*! \return size of data in database [bytes],  header included  */
   size_t packed_size() const;

   /// construct blob from native vector
   /*!  \param  vec  vector of data to be stored in blob
        \param  ctyp compression type. 0=no compression, 1=miniz, 2=lzma  */
   template <typename T>
   sqBlob(const vector<T>& vec, size_t ctyp);

   /// Unpack the blob as a vector of given native type
   /*!  \param  vec  vector returned */
   template <typename T>
   bool get_vector(vector<T>& vec) const;

   /// construct blob from native, *uncompressed* byte array
   /*!  \param  data native byte array with uncompressed blob data
        \param  nbytes number of bytes in array
        \param  ctyp compression type. 0=no compression, 1=miniz, 2=lzma  */
   sqBlob(const unsigned char* data, size_t nbytes, size_t ctyp);

   /// pack and optionally compress the data
   /*!  \param  ctyp 0=no compression, 1=miniz, 2=lzma
        \param  data uncompressed data
        \param  nbytes length of data buffer  */
   void pack_blob(size_t ctyp, const unsigned char* data, size_t nbytes);

   /// return raw blob data as stored, without any unpacking
   /*! \return raw blob data as stored, without any unpacking */
   const vector<unsigned char>& raw_data() const { return m_data; }

private:
   /// \privatesection (hidden in documentation)

   // this constructor is ONLY for use when reading from database or from external files
   sqBlob(const unsigned char* data, size_t nbytes);

   // unpack the user data into uncompressed user buffer
   size_t unpack_blob(unsigned char* data, size_t max_bytes) const;

   // raw, low level access to header+data, possibly compressed
   const unsigned char* data() const;

   // header describing whether data are compressed in database
   struct OP_LITE_PUBLIC Header {
      Header();
      Header(size_t offset, size_t ctyp, size_t usiz, size_t csiz);
      Header(IDint64 offset, IDint64 ctyp, IDint64 usiz, IDint64 csiz);
      size_t hsiz() const { return (size_t)hval[0]; }     // header size
      size_t ctyp() const { return (size_t)hval[1]; }     // compression type, 0=no compression, 1=miniz, 2=lzma
      size_t usiz() const { return (size_t)hval[2]; }     // uncompressed size
      size_t csiz() const { return (size_t)hval[3]; }     // compressed size
      IDint64 hval[4];
   };
private:
   Header                m_header; // header duplicate for easy access
   vector<unsigned char> m_data;   // actual data stored in SQL, including header
};

template <typename T>
sqBlob::sqBlob(const vector<T>& vec, size_t ctyp)
{
   size_t nbytes = sizeof(T)*vec.size();
   pack_blob(ctyp,(unsigned char*)&vec[0],nbytes);
}

template <typename T>
bool sqBlob::get_vector(vector<T>& vec) const
{
   vec.clear();
   size_t nbytes = m_header.usiz();
   if(nbytes > 0){
      vec.resize(nbytes/sizeof(T));
      unpack_blob((unsigned char*)&vec[0],nbytes);
      return true;
   }
   return false;
}


template <typename T>
size_t sqBlob::usize() const
{
   return m_header.usiz()/sizeof(T);
}


#endif // SQBLOB_H
