//
// J2735 Encode
//

#include "MessageFrame.h"

static int msg_count = 1;

int j2735_encode(const char *raw, int size, char *buf, int max)
{
  // assert
  if (!raw || !buf)
    return -1;

  // clip
  if (size > 1023)
    size = 1023;

  // storage
  MessageFrame_t  frame;
  memset(&frame, 0, sizeof(frame));
  RTCMmessageList_t list;
  memset(&list, 0, sizeof(list));
  RTCMmessage_t     msg;
  memset(&msg, 0, sizeof(msg));
  
  // frame
  frame.messageId = DSRCmsgID_rtcmCorrections_D;   // RTCM
  frame.value.present = MessageFrame__value_PR_RTCMcorrections;

  // corrections
  RTCMcorrections_t *rtcm = &frame.value.choice.RTCMcorrections;
  rtcm->msgCnt = msg_count++;
  if (msg_count>=128)
    msg_count = 1;
  rtcm->rev = RTCM_Revision_rtcmRev2;

  // message list
//  RTCMmessageList_t *plist = &list;
//  rtcm->msgs.list.array = &plist;
  rtcm->msgs.list.count = 1;
  rtcm->msgs.list.size = 1;
  
  // message
  msg.buf = (void *)raw;
  msg.size = size;
  RTCMmessage_t *pmsg = &msg;
  rtcm->msgs.list.array = &pmsg;
  list.list.array = &pmsg;
  list.list.count = 1;
  list.list.size = 1;
  
#ifdef CONSTRAINT_CHECKING
  // walk
  char err[200];
  size_t len = sizeof(err);
  if (asn_check_constraints(&asn_DEF_MessageFrame, &frame, err, &len) != 0) {
    fprintf(stderr, "%s\n", err);
    return -1;
  }
#endif

  // encode
  asn_enc_rval_t rc;
  rc = asn_encode_to_buffer(0, ATS_UNALIGNED_CANONICAL_PER, &asn_DEF_MessageFrame, &frame, buf, max);
   
  // check
  if (rc.encoded == -1)
    return -1;
  else if (rc.encoded > max)
    fprintf(stderr, "Encoding buffer is too small\n");

  return rc.encoded;
}
