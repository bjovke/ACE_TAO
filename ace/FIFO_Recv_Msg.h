/* -*- C++ -*- */
// $Id$

// ============================================================================
//
// = LIBRARY
//    ace
//
// = FILENAME
//    FIFO_Recv_Msg.h
//
// = AUTHOR
//    Doug Schmidt
//
// ============================================================================

#ifndef ACE_FIFO_RECV_MSG_H
#include "ace/pre.h"
#define ACE_FIFO_RECV_MSG_H

#include "ace/FIFO_Recv.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class ACE_Export ACE_FIFO_Recv_Msg : public ACE_FIFO_Recv
{
  // = TITLE
  //     Receiver side for the record oriented C++ wrapper for UNIX FIFOs.
public:
  // = Initialization methods.
  ACE_FIFO_Recv_Msg (void);
  // Default constructor.

  ACE_FIFO_Recv_Msg (const ASYS_TCHAR *rendezvous,
                     int flags = O_CREAT | O_RDONLY,
                     int perms = ACE_DEFAULT_FILE_PERMS,
                     int persistent = 1,
                     LPSECURITY_ATTRIBUTES sa = 0);
  // Open up a record-oriented named pipe for reading.

  int open (const ASYS_TCHAR *rendezvous,
            int flags = O_CREAT | O_RDONLY,
            int perms = ACE_DEFAULT_FILE_PERMS,
            int persistent = 1,
            LPSECURITY_ATTRIBUTES sa = 0);
  // Open up a record-oriented named pipe for reading.

  ssize_t recv (ACE_Str_Buf &msg);
  // Recv <msg> as an ACE_Str_Buf.

  ssize_t recv (void *buf, size_t len);
  // Recv <msg> as a buffer.

#if defined (ACE_HAS_STREAM_PIPES)
  ssize_t recv (ACE_Str_Buf *data,
                ACE_Str_Buf *cntl,
                int *flags);
  // Recv <data> and <cntl> message via Stream pipes.

  ssize_t recv (int *band,
                ACE_Str_Buf *data,
                ACE_Str_Buf *cntl,
                int *flags);
  // Recv <data> and <cntl> message via Stream pipes in "band" mode.
#endif /* ACE_HAS_STREAM_PIPES */

  void dump (void) const;
  // Dump the state of an object.

  ACE_ALLOC_HOOK_DECLARE;
  // Declare the dynamic allocation hooks.
};

#if !defined (ACE_LACKS_INLINE_FUNCTIONS)
#include "ace/FIFO_Recv_Msg.i"
#endif

#include "ace/post.h"
#endif /* ACE_FIFO_RECV_MSG_H */
