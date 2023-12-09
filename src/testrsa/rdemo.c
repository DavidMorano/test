/* RDEMO.C - RSAREF demonstration program
 */

/* Copyright (C) 1991-4 RSA Laboratories, a division of RSA Data
   Security, Inc. All rights reserved.
 */

#include <stdio.h>
#include <string.h>

#include "rsaglobal.h"
#include "rsaref.h"

int main PROTO_LIST ((int, char **));
static int SetOptions PROTO_LIST ((int, char **));
static void InitRandomStruct PROTO_LIST ((R_RANDOM_STRUCT *));
static void DoSignFile PROTO_LIST ((void));
static void DoVerifyFile PROTO_LIST ((void));
static void DoSealFile PROTO_LIST ((R_RANDOM_STRUCT *));
static void DoOpenFile PROTO_LIST ((void));
static void DoGenerateKeys PROTO_LIST ((R_RANDOM_STRUCT *));
static void WriteKeypair3 PROTO_LIST ((void));
static void WriteBigInteger PROTO_LIST
  ((FILE *, unsigned char *, unsigned int));
static int ReadInit PROTO_LIST ((FILE **, char *));
static int ReadUpdate PROTO_LIST
  ((FILE *, unsigned char *, unsigned int *, unsigned int));
static void ReadFinal PROTO_LIST ((FILE *));
static int ReadBlock PROTO_LIST
  ((unsigned char *, unsigned int *, unsigned int, char *));
static int WriteInit PROTO_LIST ((FILE **, char *));
static int WriteUpdate PROTO_LIST ((FILE *, unsigned char *, unsigned int));
static void WriteFinal PROTO_LIST ((FILE *));
static int WriteBlock PROTO_LIST ((unsigned char *, unsigned int, char *));
static int GetPublicKey PROTO_LIST ((R_RSA_PUBLIC_KEY **));
static int GetPrivateKey PROTO_LIST ((R_RSA_PRIVATE_KEY **));
static int GetDigestAlgorithm PROTO_LIST ((int *));
static int GetEncryptionAlgorithm PROTO_LIST ((int *));
static void PrintMessage PROTO_LIST ((char *));
static void PrintError PROTO_LIST ((char *, int));
static void GetCommand PROTO_LIST ((char *, unsigned int, char *));

static int SILENT_PROMPT = 0;

static R_RSA_PUBLIC_KEY PUBLIC_KEY1 = {
  512,
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x76, 0x47, 0x97, 0xb8, 0xbe, 0xc8, 0x97,
   0x2a, 0x0e, 0xd8, 0xc9, 0x0a, 0x8c, 0x33, 0x4d, 0xd0, 0x49, 0xad, 0xd0,
   0x22, 0x2c, 0x09, 0xd2, 0x0b, 0xe0, 0xa7, 0x9e, 0x33, 0x89, 0x10, 0xbc,
   0xae, 0x42, 0x20, 0x60, 0x90, 0x6a, 0xe0, 0x22, 0x1d, 0xe3, 0xf3, 0xfc,
   0x74, 0x7c, 0xcf, 0x98, 0xae, 0xcc, 0x85, 0xd6, 0xed, 0xc5, 0x2d, 0x93,
   0xd5, 0xb7, 0x39, 0x67, 0x76, 0x16, 0x05, 0x25},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01}
};

static R_RSA_PRIVATE_KEY PRIVATE_KEY1 = {
  512,
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xc0, 0x76, 0x47, 0x97, 0xb8, 0xbe, 0xc8, 0x97,
   0x2a, 0x0e, 0xd8, 0xc9, 0x0a, 0x8c, 0x33, 0x4d, 0xd0, 0x49, 0xad, 0xd0,
   0x22, 0x2c, 0x09, 0xd2, 0x0b, 0xe0, 0xa7, 0x9e, 0x33, 0x89, 0x10, 0xbc,
   0xae, 0x42, 0x20, 0x60, 0x90, 0x6a, 0xe0, 0x22, 0x1d, 0xe3, 0xf3, 0xfc,
   0x74, 0x7c, 0xcf, 0x98, 0xae, 0xcc, 0x85, 0xd6, 0xed, 0xc5, 0x2d, 0x93,
   0xd5, 0xb7, 0x39, 0x67, 0x76, 0x16, 0x05, 0x25},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x1a, 0xe3, 0x6b, 0x75, 0x22, 0xf6, 0x64, 0x87,
   0xd9, 0xf4, 0x61, 0x0d, 0x15, 0x50, 0x29, 0x0a, 0xc2, 0x02, 0xc9, 0x29,
   0xbe, 0xdc, 0x70, 0x32, 0xcc, 0x3e, 0x02, 0xac, 0xf3, 0x7e, 0x3e, 0xbc,
   0x1f, 0x86, 0x6e, 0xe7, 0xef, 0x7a, 0x08, 0x68, 0xd2, 0x3a, 0xe2, 0xb1,
   0x84, 0xc1, 0xab, 0xd6, 0xd4, 0xdb, 0x8e, 0xa9, 0xbe, 0xc0, 0x46, 0xbd,
   0x82, 0x80, 0x37, 0x27, 0xf2, 0x88, 0x87, 0x01},
  {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdf, 0x02, 0xb6, 0x15,
    0xfe, 0x15, 0x92, 0x8f, 0x41, 0xb0, 0x2b, 0x58, 0x6b, 0x51, 0xc2, 0xc0,
    0x22, 0x60, 0xca, 0x39, 0x68, 0x18, 0xca, 0x4c, 0xba, 0x60, 0xbb, 0x89,
    0x24, 0x65, 0xbe, 0x35},
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0xee, 0xb6, 0x0d,
    0x54, 0x35, 0x18, 0xb4, 0xac, 0x74, 0x83, 0x4a, 0x05, 0x46, 0xc5, 0x07,
    0xf2, 0xe9, 0x1e, 0x38, 0x9a, 0x87, 0xe2, 0xf2, 0xbe, 0xcc, 0x6f, 0x8c,
    0x67, 0xd1, 0xc9, 0x31}},
  {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x48, 0x7e, 0x99,
    0xe3, 0x75, 0xc3, 0x8d, 0x73, 0x21, 0x12, 0xd9, 0x7d, 0x6d, 0xe8, 0x68,
    0x7f, 0xda, 0xfc, 0x5b, 0x6b, 0x5f, 0xb1, 0x6e, 0x72, 0x97, 0xd3, 0xbd,
    0x1e, 0x43, 0x55, 0x99},
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xb5, 0x50, 0xde,
    0x64, 0x37, 0x77, 0x4d, 0xb0, 0x57, 0x77, 0x18, 0xed, 0x6c, 0x77, 0x07,
    0x24, 0xee, 0xe4, 0x66, 0xb4, 0x31, 0x14, 0xb5, 0xb6, 0x9c, 0x43, 0x59,
    0x1d, 0x31, 0x32, 0x81}},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x4c, 0x79, 0xc4,
   0xb9, 0xbe, 0xa9, 0x7c, 0x25, 0xe5, 0x63, 0xc9, 0x40, 0x7a, 0x2d, 0x09,
   0xb5, 0x73, 0x58, 0xaf, 0xe0, 0x9a, 0xf6, 0x7d, 0x71, 0xf8, 0x19, 0x8c,
   0xb7, 0xc9, 0x56, 0xb8}
};

static R_RSA_PUBLIC_KEY PUBLIC_KEY2 = {
  512,
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe5, 0xf2, 0x0d, 0xce, 0x83, 0x32, 0x30, 0xe4,
   0x51, 0xd5, 0x0c, 0x79, 0xa5, 0x34, 0x23, 0xfb, 0x5f, 0xfb, 0xa0, 0xff,
   0x5c, 0x77, 0x96, 0xa9, 0x2c, 0x35, 0xee, 0x53, 0x02, 0xb7, 0x89, 0x2d,
   0xf0, 0x78, 0x49, 0xdd, 0xdc, 0x27, 0x79, 0x8b, 0x69, 0xa2, 0x5e, 0x7a,
   0x40, 0x27, 0x43, 0x82, 0x7a, 0xc4, 0xfa, 0x50, 0x21, 0x1f, 0x15, 0x35,
   0xc3, 0x93, 0x46, 0x62, 0xcd, 0xd4, 0x26, 0x89},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01}
};

static R_RSA_PRIVATE_KEY PRIVATE_KEY2 = {
  512,
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe5, 0xf2, 0x0d, 0xce, 0x83, 0x32, 0x30, 0xe4,
   0x51, 0xd5, 0x0c, 0x79, 0xa5, 0x34, 0x23, 0xfb, 0x5f, 0xfb, 0xa0, 0xff,
   0x5c, 0x77, 0x96, 0xa9, 0x2c, 0x35, 0xee, 0x53, 0x02, 0xb7, 0x89, 0x2d,
   0xf0, 0x78, 0x49, 0xdd, 0xdc, 0x27, 0x79, 0x8b, 0x69, 0xa2, 0x5e, 0x7a,
   0x40, 0x27, 0x43, 0x82, 0x7a, 0xc4, 0xfa, 0x50, 0x21, 0x1f, 0x15, 0x35,
   0xc3, 0x93, 0x46, 0x62, 0xcd, 0xd4, 0x26, 0x89},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x8e, 0x6b, 0x48, 0x4f, 0xe3, 0x04, 0x60, 0x31,
   0xd9, 0xd9, 0x59, 0xdb, 0xb2, 0x0d, 0xc4, 0x47, 0x7a, 0x60, 0x70, 0x8c,
   0x19, 0x2a, 0x5c, 0x9f, 0x35, 0x29, 0xc6, 0x0d, 0x95, 0xfe, 0x35, 0x30,
   0x99, 0x54, 0xda, 0x99, 0x90, 0xe3, 0x3e, 0x1d, 0xdb, 0x32, 0x7b, 0x1d,
   0x26, 0xf2, 0x9a, 0xab, 0x03, 0x09, 0x77, 0xba, 0x4f, 0x43, 0xdb, 0xda,
   0xc8, 0x1f, 0x12, 0xd6, 0xf2, 0x57, 0x1a, 0x31},
  {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x6c, 0x5d, 0xb7,
    0x7b, 0xa7, 0x9e, 0x2f, 0x4a, 0x26, 0xec, 0xe0, 0x1b, 0x2a, 0x5f, 0x42,
    0x04, 0x87, 0xb4, 0xc4, 0x68, 0x80, 0xf3, 0x09, 0xe5, 0x48, 0x00, 0x30,
    0x6f, 0x54, 0x04, 0x75},
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xd6, 0x25, 0x08,
    0xe5, 0x54, 0x19, 0xa3, 0x98, 0x9d, 0x77, 0x92, 0x18, 0xba, 0x9c, 0x00,
    0xda, 0x69, 0xee, 0x84, 0xf9, 0x10, 0xe5, 0xda, 0xf0, 0x7d, 0x78, 0x6c,
    0x92, 0xd8, 0xc7, 0x45}},
  {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x03, 0x32, 0x71,
    0x69, 0x3c, 0x85, 0xca, 0x20, 0xca, 0x0b, 0x22, 0xb2, 0xc2, 0x03, 0x00,
    0xce, 0x20, 0x3c, 0xf4, 0xa5, 0x93, 0x4f, 0xe2, 0x1f, 0xf7, 0x07, 0x5c,
    0x64, 0xc8, 0x24, 0x21},
   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xf1, 0xde, 0x01,
    0x07, 0xe9, 0x1b, 0xfa, 0x7e, 0x51, 0x6b, 0x62, 0xb2, 0x29, 0x6b, 0xb6,
    0x0f, 0xeb, 0xd5, 0xf8, 0x08, 0xc1, 0x7c, 0x90, 0xd6, 0x3f, 0xa0, 0xa4,
    0x2e, 0x30, 0xef, 0xb5}},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x01, 0x60, 0x46,
   0x90, 0x85, 0xaf, 0x6f, 0xa2, 0x8d, 0x6a, 0x1d, 0x3e, 0xfd, 0x56, 0xd7,
   0x57, 0x5e, 0x00, 0x30, 0x5b, 0x49, 0x6c, 0xc4, 0x85, 0xf5, 0x1c, 0x39,
   0xef, 0x0b, 0x4b, 0x28}
};

R_RSA_PUBLIC_KEY PUBLIC_KEY3;
R_RSA_PRIVATE_KEY PRIVATE_KEY3;
int KEYPAIR3_READY = 0;

int main(argc, argv)
int argc;
char *argv[];
{
  R_RANDOM_STRUCT randomStruct;
  char command[80];
  int done = 0;

  if (SetOptions (argc, argv))
    return (0);
  
  InitRandomStruct (&randomStruct);
  PrintMessage
    ("NOTE: When saving to a file, a filename of \"-\" will output to the screen.");

  while (!done) {
    PrintMessage ("");
    PrintMessage ("S - Sign a file");
    PrintMessage ("V - Verify a signed file");
    PrintMessage ("E - sEal a file");
    PrintMessage ("O - Open a sealed file");
    PrintMessage ("G - Generate a keypair (may take a long time)");
    PrintMessage ("Q - Quit");
    GetCommand (command, sizeof (command), "  Enter choice");
    
    switch (*command) {
    case '#':
      /* entered a comment */
      break;
      
    case 's':
    case 'S':
      DoSignFile ();
      break;
      
    case 'v':
    case 'V':
      DoVerifyFile ();
      break;
      
    case 'e':
    case 'E':
      DoSealFile (&randomStruct);
      break;

    case 'o':
    case 'O':
      DoOpenFile ();
      break;
      
    case 'g':
    case 'G':
      DoGenerateKeys (&randomStruct);
      break;
      
    case '\0':
    case 'Q':
    case 'q':
      done = 1;
      break;
      
    default:
      PrintError ("ERROR: Unrecognized command.  Try again.", 0);
      break;
    }
  }
  
  R_RandomFinal (&randomStruct);
  R_memset ((POINTER)&PRIVATE_KEY3, 0, sizeof (PRIVATE_KEY3));
  return (0);
}
/* end subroutine (main) */


/* Set options from command line and return 0 for success, 1 for bad format.
 */
static int SetOptions (argc, argv)
int argc;
char *argv[];
{
  int i, status = 0;
  
  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      status = 1;
      break;
    }
    
    if (argv[i][1] == 's')
      SILENT_PROMPT = 1;
    else {
      status = 1;
      break;
    }
  }

  if (status)
    puts ("Usage: rdemo [-s]\n\
  -s silent prompts\n");

  return (status);
}

/* Initialize the random structure with all zero seed bytes for test purposes.
   NOTE that this will cause the output of the "random" process to be
     the same every time.  To produce random bytes, the random struct
     needs random seeds!
 */
static void InitRandomStruct (randomStruct)
R_RANDOM_STRUCT *randomStruct;
{
  static unsigned char seedByte = 0;
  unsigned int bytesNeeded;
  
  R_RandomInit (randomStruct);
  
  /* Initialize with all zero seed bytes, which will not yield an actual
       random number output.
   */
  while (1) {
    R_GetRandomBytesNeeded (&bytesNeeded, randomStruct);
    if (bytesNeeded == 0)
      break;
    
    R_RandomUpdate (randomStruct, &seedByte, 1);
  }
}

static void DoSignFile ()
{
  FILE *file;
  R_RSA_PRIVATE_KEY *privateKey;
  R_SIGNATURE_CTX context;
  int digestAlgorithm, status;
  unsigned char partIn[24], signature[MAX_SIGNATURE_LEN];
  unsigned int partInLen, signatureLen;

  status = 0;

  if (ReadInit (&file, "  Enter filename of content to sign"))
    return;

  do {
    if (GetPrivateKey (&privateKey))
      break;

    if (GetDigestAlgorithm (&digestAlgorithm))
      break;

    if ((status = R_SignInit (&context, digestAlgorithm)) != 0)
      break;

    while (!ReadUpdate (file, partIn, &partInLen, sizeof (partIn)))
      if ((status = R_SignUpdate (&context, partIn, partInLen)) != 0)
        break;
    if (status)
      break;

    if ((status = R_SignFinal
         (&context, signature, &signatureLen, privateKey)) != 0)
      break;

    if (WriteBlock
        (signature, signatureLen, "  Enter filename to save the signature"))
      break;
  } while (0);

  ReadFinal (file);

  if (status)
    PrintError ("signing file", status);

  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)partIn, 0, sizeof (partIn));
}

static void DoVerifyFile ()
{
  FILE *file;
  R_RSA_PUBLIC_KEY *publicKey;
  R_SIGNATURE_CTX context;
  int digestAlgorithm, status;
  unsigned char partIn[16], signature[MAX_SIGNATURE_LEN];
  unsigned int partInLen, signatureLen;

  status = 0;

  if (ReadInit (&file, "  Enter name of file to verify"))
    return;

  do {
    if (GetPublicKey (&publicKey))
      break;

    if (GetDigestAlgorithm (&digestAlgorithm))
      break;

    if (ReadBlock
        (signature, &signatureLen, sizeof (signature),
         "  Enter filename of signature"))
      break;

    if ((status = R_VerifyInit (&context, digestAlgorithm)) != 0)
      break;

    while (!ReadUpdate (file, partIn, &partInLen, sizeof (partIn)))
      if ((status = R_VerifyUpdate (&context, partIn, partInLen)) != 0)
        break;
    if (status)
      break;

    if ((status = R_VerifyFinal
         (&context, signature, signatureLen, publicKey)) != 0)
      break;

    PrintMessage ("Signature verified.");
  } while (0);

  ReadFinal (file);

  if (status)
    PrintError ("verifying file", status);

  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)partIn, 0, sizeof (partIn));
}

static void DoSealFile (randomStruct)
R_RANDOM_STRUCT *randomStruct;
{
  FILE *inFile, *outFile;
  R_ENVELOPE_CTX context;
  R_RSA_PUBLIC_KEY *publicKey;
  int encryptionAlgorithm, status;
  unsigned char encryptedKey[MAX_ENCRYPTED_KEY_LEN], *encryptedKeys[1],
    iv[8], partIn[24], partOut[31];
  unsigned int encryptedKeyLen, partInLen, partOutLen;

  status = 0;

  if (ReadInit (&inFile, "  Enter filename of content to seal"))
    return;
  if (WriteInit (&outFile, "  Enter filename to save the encrypted content")) {
    ReadFinal (inFile);
    return;
  }

  do {
    if (GetPublicKey (&publicKey))
      break;

    if (GetEncryptionAlgorithm (&encryptionAlgorithm))
      break;

    encryptedKeys[0] = encryptedKey;

    if ((status = R_SealInit
         (&context, encryptedKeys, &encryptedKeyLen, iv, 1, &publicKey,
          encryptionAlgorithm, randomStruct)) != 0)
      break;

    while (!ReadUpdate (inFile, partIn, &partInLen, sizeof (partIn))) {
      if ((status = R_SealUpdate
           (&context, partOut, &partOutLen, partIn, partInLen)) != 0)
        break;
      WriteUpdate (outFile, partOut, partOutLen);
    }
    if (status)
      break;

    if ((status = R_SealFinal (&context, partOut, &partOutLen)))
      break;
    WriteUpdate (outFile, partOut, partOutLen);
  
    if (WriteBlock
        (encryptedKey, encryptedKeyLen,
         "  Enter filename to save the encrypted key"))
      break;
    if (WriteBlock
        (iv, 8, "  Enter filename to save the initializing vector"))
      break;
  } while (0);
  
  ReadFinal (inFile);
  WriteFinal (outFile);

  if (status)
    PrintError ("sealing file", status);

  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)partIn, 0, sizeof (partIn));
}

static void DoOpenFile ()
{
  FILE *inFile, *outFile;
  R_ENVELOPE_CTX context;
  R_RSA_PRIVATE_KEY *privateKey;
  int encryptionAlgorithm, status;
  unsigned char encryptedKey[MAX_ENCRYPTED_KEY_LEN], iv[8], partIn[24],
    partOut[31];
  unsigned int encryptedKeyLen, ivLen, partInLen, partOutLen;

  status = 0;

  if (ReadInit (&inFile, "  Enter filename of encrypted content to open"))
    return;

  if (WriteInit (&outFile, "  Enter filename to save the recovered content")) {
    ReadFinal (inFile);
    return;
  }

  do {
    if (GetPrivateKey (&privateKey))
      break;

    if (GetEncryptionAlgorithm (&encryptionAlgorithm))
      break;

    if (ReadBlock
        (encryptedKey, &encryptedKeyLen, sizeof (encryptedKey),
         "  Enter filename of the encrypted key"))
      break;  
    if (ReadBlock
        (iv, &ivLen, 8, "  Enter filename of the initializing vector"))
      break;

    if ((status = R_OpenInit
         (&context, encryptionAlgorithm, encryptedKey, encryptedKeyLen, iv,
          privateKey)) != 0)
      break;
    
    while (!ReadUpdate (inFile, partIn, &partInLen, sizeof (partIn))) {
      if ((status = R_OpenUpdate
           (&context, partOut, &partOutLen, partIn, partInLen)) != 0)
        break;
      WriteUpdate (outFile, partOut, partOutLen);
    }
    if (status)
      break;

    if ((status = R_OpenFinal (&context, partOut, &partOutLen)) != 0)
      break;
    WriteUpdate (outFile, partOut, partOutLen);
  } while (0);
  
  ReadFinal (inFile);
  WriteFinal (outFile);

  if (status)
    PrintError ("opening file", status);

  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)partOut, 0, sizeof (partOut));
}

static void DoGenerateKeys (randomStruct)
R_RANDOM_STRUCT *randomStruct;
{
  R_RSA_PROTO_KEY protoKey;
  char command[80];
  int status, keySize;

  GetCommand
    (command, sizeof (command),
     "  Enter key size in bits, (508 to 1024)");
  if (! *command)
    return;
  sscanf (command, "%d", &keySize);
  
  protoKey.bits = (unsigned int)keySize;
  protoKey.useFermat4 = 1;
  
  if (status = R_GeneratePEMKeys
      (&PUBLIC_KEY3, &PRIVATE_KEY3, &protoKey, randomStruct)) {
    PrintError ("generating keys", status);
    return;
  }

  PrintMessage ("Public key 3 and private key 3 are now ready to use.");
  KEYPAIR3_READY = 1;
  
  WriteKeypair3 ();
}

static void WriteKeypair3 ()
{
  FILE *file;
  char filename[256];
  
  while (1) {
    GetCommand
      (filename, sizeof (filename),
       "  Enter filename to save the keypair");
    if (! *filename)
      return;
    
    if (filename[0] == '-' && filename[1] == '\0') {
      /* use stdout */
      file = stdout;
      break;
    }
    if ((file = fopen (filename, "w")) != NULL)
      /* successfully opened */
      break;
    
    PrintError ("ERROR: Cannot open a file with that name.  Try again.", 0);
  }

  fprintf (file, "Public Key, %u bits:\n", PUBLIC_KEY3.bits);
  fprintf (file, "  modulus: ");
  WriteBigInteger (file, PUBLIC_KEY3.modulus, sizeof (PUBLIC_KEY3.modulus));
  fprintf (file, "  exponent: ");
  WriteBigInteger (file, PUBLIC_KEY3.exponent, sizeof (PUBLIC_KEY3.exponent));

  fprintf (file, "\nPrivate Key, %u bits:\n", PRIVATE_KEY3.bits);
  fprintf (file, "  modulus: ");
  WriteBigInteger (file, PRIVATE_KEY3.modulus, sizeof (PRIVATE_KEY3.modulus));
  fprintf (file, "  public exponent: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.publicExponent, sizeof (PRIVATE_KEY3.publicExponent));
  fprintf (file, "  exponent: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.exponent, sizeof (PRIVATE_KEY3.exponent));
  fprintf (file, "  prime 1: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.prime[0], sizeof (PRIVATE_KEY3.prime[0]));
  fprintf (file, "  prime 2: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.prime[1], sizeof (PRIVATE_KEY3.prime[1]));
  fprintf (file, "  prime exponent 1: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.primeExponent[0],
     sizeof (PRIVATE_KEY3.primeExponent[0]));
  fprintf (file, "  prime exponent 2: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.primeExponent[1],
     sizeof (PRIVATE_KEY3.primeExponent[1]));
  fprintf (file, "  coefficient: ");
  WriteBigInteger
    (file, PRIVATE_KEY3.coefficient, sizeof (PRIVATE_KEY3.coefficient));

  if (file != stdout)
    fclose (file);
}

/* Write the byte string 'integer' to 'file', skipping over leading zeros.
 */
static void WriteBigInteger (file, integer, integerLen)
FILE *file;
unsigned char *integer;
unsigned int integerLen;
{
  while (*integer == 0 && integerLen > 0) {
    integer++;
    integerLen--;
  }
  
  if (integerLen == 0) {
    /* Special case, just print a zero. */
    fprintf (file, "00\n");
    return;
  }
  
  for (; integerLen > 0; integerLen--)
    fprintf (file, "%02x ", (unsigned int)(*integer++));

  fprintf (file, "\n");
}

/* Ask the user to use public key 1, 2 or 3 and point publicKey to
     the answer.
   Return 0 on success or 1 if user cancels by entering a blank.
 */
static int GetPublicKey (publicKey)
R_RSA_PUBLIC_KEY **publicKey;
{
  char command[80];
  
  while (1) {
    if (!KEYPAIR3_READY)
      GetCommand (command, sizeof (command), "  Public key 1 or 2?");
    else
      GetCommand (command, sizeof (command), "  Public key 1, 2 or 3?");

    switch (*command) {
    case '\0':
      return (1);
      
    case '1':
      *publicKey = &PUBLIC_KEY1;
      return (0);
      
    case '2':
      *publicKey = &PUBLIC_KEY2;
      return (0);
      
    case '3':
      if (!KEYPAIR3_READY)
        break;
      *publicKey = &PUBLIC_KEY3;
      return (0);
      
    default:
      if (KEYPAIR3_READY)
        PrintError ("ERROR: Please enter 1, 2 or 3.  Try again.", 0);
      else
        PrintError ("ERROR: Please enter 1 or 2.  Try again.", 0);
      break;
    }
  }
}

/* Ask the user to use private key 1, 2 or 3 and point privateKey to
     the answer.
   Return 0 on success or 1 if user cancels by entering a blank.
 */
static int GetPrivateKey (privateKey)
R_RSA_PRIVATE_KEY **privateKey;
{
  char command[80];
  
  while (1) {
    if (!KEYPAIR3_READY)
      GetCommand (command, sizeof (command), "  Public key 1 or 2?");
    else
      GetCommand (command, sizeof (command), "  Public key 1, 2 or 3?");

    switch (*command) {
    case '\0':
      return (1);
      
    case '1':
      *privateKey = &PRIVATE_KEY1;
      return (0);
      
    case '2':
      *privateKey = &PRIVATE_KEY2;
      return (0);
      
    case '3':
      if (!KEYPAIR3_READY)
        break;
      *privateKey = &PRIVATE_KEY3;
      return (0);
      
    default:
      if (KEYPAIR3_READY)
        PrintError ("ERROR: Please enter 1, 2 or 3.  Try again.", 0);
      else
        PrintError ("ERROR: Please enter 1 or 2.  Try again.", 0);
      break;
    }
  }
}

/* Ask the user to use MD2 or MD5 and point digestAlgorithm to the
     answer.
   Return 0 on success or 1 if user cancels by entering a blank.
 */
static int GetDigestAlgorithm (digestAlgorithm)
int *digestAlgorithm;
{
  char command[80];
  
  while (1) {
    GetCommand (command, sizeof (command), "  MD2 or MD5 (2 or 5)?");

    switch (*command) {
    case '\0':
      return (1);
      
    case '2':
      *digestAlgorithm = DA_MD2;
      return (0);
      
    case '5':
      *digestAlgorithm = DA_MD5;
      return (0);
      
    default:
      PrintError ("ERROR: Please enter 2 or 5.  Try again.", 0);
      break;
    }
  }
}

/* Ask the user to use DES, DESX, DES-EDE2, or DES-EDE3, and point
     encryptionAlgorithm to the answer.
   Return 0 on success or 1 if user cancels by entering a blank.
 */
static int GetEncryptionAlgorithm (encryptionAlgorithm)
int *encryptionAlgorithm;
{
  char command[80];
  
  while (1) {
    GetCommand
      (command, sizeof (command),
       "  DES, DESX, DES-EDE2 or DES-EDE3 (1, X, 2 or 3)?");

    switch (*command) {
    case '\0':
      return (1);
      
    case '1':
      *encryptionAlgorithm = EA_DES_CBC;
      return (0);
      
    case 'x':
    case 'X':
      *encryptionAlgorithm = EA_DESX_CBC;
      return (0);
      
    case '2':
      *encryptionAlgorithm = EA_DES_EDE2_CBC;
      return (0);
      
    case '3':
      *encryptionAlgorithm = EA_DES_EDE3_CBC;
      return (0);
      
    default:
      PrintError ("ERROR: Please enter 1, X, 2 or 3.  Try again.", 0);
      break;
    }
  }
}

/* Ask for the filename using the given prompt string and open it
     for reading.
   Return 0 on success or 1 if error or if user cancels by entering a blank.
 */
static int ReadInit (file, prompt) 
FILE **file;
char *prompt;
{
  char filename[256];
  
  while (1) {
    GetCommand (filename, sizeof (filename), prompt);
    if (! *filename)
      return (1);
    
    if ((*file = fopen (filename, "rb")) != NULL)
      /* successfully opened */
      break;
    
    PrintError ("ERROR: Cannot open a file with that name.  Try again.", 0);
  }

  return (0);
}

/* Read a block of up to length maxPartOutLen bytes from file, storing
     it in partOut and returning its length in partOutLen.
   Return 0 on success or 1 if error or end of file.
 */
static int ReadUpdate (file, partOut, partOutLen, maxPartOutLen)
FILE *file;
unsigned char *partOut;
unsigned int *partOutLen;
unsigned int maxPartOutLen;
{
  int status;
  
  /* fread () returns the number of items read in.
   */
  *partOutLen = fread (partOut, 1, maxPartOutLen, file);

  status = 0;
  if (ferror (file)) {
    PrintError ("ERROR: Cannot read file.", 0);
    status = 1;
  }
  if (*partOutLen == 0 && feof (file))
    status = 1;

  return (status);
}

/* Close file.
 */
static void ReadFinal (file)
FILE *file;
{
  fclose (file);
}

/* Read a file of up to length maxBlockLen bytes, storing it in
     block and returning its length in blockLen.
   Ask for the filename using the given prompt string.
   Return 0 on success or 1 if error or if user cancels by entering a blank.
 */
static int ReadBlock (block, blockLen, maxBlockLen, prompt) 
unsigned char *block;
unsigned int *blockLen;
unsigned int maxBlockLen;
char *prompt;
{
  FILE *file;
  int status;
  unsigned char *dummy;
  unsigned int dummyLen;

  if (ReadInit (&file, prompt))
    return (1);

  if ((status = ReadUpdate (file, block, blockLen, maxBlockLen)) == 0) {
    if (*blockLen == maxBlockLen)
      /* Read exactly maxBlockLen bytes, so reading one more will set 
           end of file if there were exactly maxBlockLen bytes in the file.
       */
      if (!ReadUpdate (file, dummy, &dummyLen, 1)) {
        PrintError ("ERROR: File is too large.", 0);
        status = 1;
      }
  }
    
  ReadFinal (file);

  return (status);
}

/* Ask for the filename using the given prompt string and open it
     for writing. 
   Return 0 on success or 1 if error or if user cancels by entering a blank.
 */
static int WriteInit (file, prompt) 
FILE **file;
char *prompt;
{
  char filename[256];
  
  while (1) {
    GetCommand (filename, sizeof (filename), prompt);
    if (! *filename)
      return (1);
    
    if (filename[0] == '-' && filename[1] == '\0') {
      /* use stdout */
      *file = stdout;
      break;
    }
    if ((*file = fopen (filename, "wb")) != NULL)
      /* successfully opened */
      break;
    
    PrintError ("ERROR: Cannot open a file with that name.  Try again.", 0);
  }

  return (0);
}

/* Write block of length partOutLen to a file.
   Return 0 on success or 1 if error.
 */
static int WriteUpdate (file, partOut, partOutLen)
FILE *file;
unsigned char *partOut;
unsigned int partOutLen;
{
  int status;

  status = 0;
  if (fwrite (partOut, 1, partOutLen, file) < partOutLen) {
    PrintError ("ERROR: Cannot write file.", 0);
    status = 1;
  }
  
  return (status);
}

/* Close file.
 */
static void WriteFinal (file)
FILE *file;
{
  if (file != stdout)
    fclose (file);
}

/* Write block of length blockLen to a file.
   Ask for the filename using the given prompt string.
   Return 0 on success or 1 if error or if user cancels by entering a blank.
 */
static int WriteBlock (block, blockLen, prompt) 
unsigned char *block;
unsigned int blockLen;
char *prompt;
{
  FILE *file;
  int status;

  if (WriteInit (&file, prompt))
    return (1);

  do {
    if ((status = WriteUpdate (file, block, blockLen)) != 0)
      break;
  
    if (file == stdout)
      /* Printing to screen, so print a new line. */
      printf ("\n");
  } while (0);

  WriteFinal (file);

  return (status);
}

static void PrintMessage (message)
char *message;
{
  if (!SILENT_PROMPT) {
    puts (message);
    fflush (stdout);
  }
}

/* If type is zero, simply print the task string, otherwise convert the
     type to a string and print task and type.
 */
static void PrintError (task, type)
char *task;
int type;
{
  char *typeString, buf[80];

  if (type == 0) {
    puts (task);
    return;
  }
  
  /* Convert the type to a string if it is recognized.
   */
  switch (type) {
  case RE_KEY:
    typeString = "Recovered DES key cannot decrypt encrypted content";
    break;
  case RE_LEN:
    typeString = "Encrypted key length or signature length is out of range";
    break;
  case RE_MODULUS_LEN:
    typeString = "Modulus length is out of range";
    break;
  case RE_PRIVATE_KEY:
    typeString = "Private key cannot encrypt message digest, or cannot decrypt encrypted key";
    break;
  case RE_PUBLIC_KEY:
    typeString = "Public key cannot encrypt data encryption key, or cannot decrypt signature";
    break;
  case RE_SIGNATURE:
    typeString = "Signature is incorrect";
    break;
    
  default:
    sprintf (buf, "Code 0x%04x", type);
    typeString = buf;
  }

  printf ("ERROR: %s while %s\n", typeString, task);  
  fflush (stdout);
}

static void GetCommand (command, maxCommandSize, prompt)
char *command;
unsigned int maxCommandSize;
char *prompt;
{
  unsigned int i;
  
  if (!SILENT_PROMPT) {
    printf ("%s (blank to cancel): \n", prompt);  
    fflush (stdout);
  }

  fgets (command, maxCommandSize, stdin);
  
  /* Replace the line terminator with a '\0'.
   */
  for (i = 0; command[i] != '\0'; i++) {
    if (command[i] == '\012' || command[i] == '\015' ||
        i == (maxCommandSize - 1)) {
      command[i] = '\0';
      return;
    }
  }
}
