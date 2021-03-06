//
// Copyright 2020 Staysail Systems, Inc. <info@staysail.tech>
// Copyright 2017 Capitar IT Group BV <info@capitar.com>
//
// This software is supplied under the terms of the MIT License, a
// copy of which should be located in the distribution where this
// file was obtained (LICENSE.txt).  A copy of the license may also be
// found online at https://opensource.org/licenses/MIT.
//

#ifndef CORE_MESSAGE_H
#define CORE_MESSAGE_H

// Internally used message API.  Again, this is not part of our public API.
// "trim" operations work from the front, and "chop" work from the end.

extern int      nni_msg_alloc(nni_msg **, size_t);
extern void     nni_msg_free(nni_msg *);
extern int      nni_msg_realloc(nni_msg *, size_t);
extern int      nni_msg_dup(nni_msg **, const nni_msg *);
extern void *   nni_msg_header(nni_msg *);
extern size_t   nni_msg_header_len(const nni_msg *);
extern void *   nni_msg_body(nni_msg *);
extern size_t   nni_msg_len(const nni_msg *);
extern int      nni_msg_append(nni_msg *, const void *, size_t);
extern int      nni_msg_insert(nni_msg *, const void *, size_t);
extern int      nni_msg_header_append(nni_msg *, const void *, size_t);
extern int      nni_msg_header_insert(nni_msg *, const void *, size_t);
extern int      nni_msg_trim(nni_msg *, size_t);
extern int      nni_msg_chop(nni_msg *, size_t);
extern void     nni_msg_clear(nni_msg *);
extern void     nni_msg_header_clear(nni_msg *);
extern int      nni_msg_header_trim(nni_msg *, size_t);
extern int      nni_msg_header_chop(nni_msg *, size_t);
extern void     nni_msg_dump(const char *, const nni_msg *);
extern void     nni_msg_header_append_u32(nni_msg *, uint32_t);
extern uint32_t nni_msg_header_trim_u32(nni_msg *);
extern uint32_t nni_msg_trim_u32(nni_msg *);
extern void     nni_msg_set_pipe(nni_msg *, uint32_t);
extern uint32_t nni_msg_get_pipe(const nni_msg *);

// Reference counting messages. This allows the same message to be
// cheaply reused instead of copied over and over again.  Callers of
// this functionality MUST be certain to use nni_msg_unique() before
// passing a message out of their control (e.g. to user programs.)
// Failure to do so will likely result in corruption.
extern void     nni_msg_clone(nni_msg *);
extern nni_msg *nni_msg_unique(nni_msg *);
// nni_msg_pull_up ensures that the message is unique, and that any
// header present is "pulled up" into the message body.  If the function
// cannot do this for any reason (out of space in the body), then NULL
// is returned.  It is the responsibility of the caller to free the
// original message in that case (same semantics as realloc).
extern nni_msg *nni_msg_pull_up(nni_msg *);


//NANOMQ MQTT
extern size_t   nni_msg_remain_len(nni_msg *m);
extern int     nni_msg_cmd_type(nni_msg *m);
extern uint8_t *nni_msg_header_ptr(const nni_msg *m);
extern uint8_t *nni_msg_variable_ptr(const nni_msg *m);
extern uint8_t *nni_msg_payload_ptr(const nni_msg *m);
extern size_t   nni_msg_remaining_len(const nni_msg *m);
extern void     nni_msg_set_payload_ptr(nni_msg *m, uint8_t * ptr);
extern void     nni_msg_set_remaining_len(nni_msg *m, size_t len);
extern void     nni_msg_set_cmd_type(nni_msg *m, uint8_t cmd);
extern void     nni_msg_set_conn_param(nni_msg *m, void *ptr);

extern conn_param *   nni_msg_get_conn_param(nni_msg *m);

typedef struct conn_param conn_param;
typedef struct conn_propt conn_propt;
typedef struct mqtt_string mqtt_string;
typedef struct mqtt_str_pair mqtt_str_pair;

struct conn_propt {
       uint8_t session_exp_int[5];
};

struct mqtt_string {
        char   * body;
        uint32_t len;
};

struct mqtt_string_pair {
        char   * key;
        uint32_t len_key;
        char   * val;
        uint32_t len_val;
};


struct mqtt_binary {
        char   * body;
        uint32_t len;
};
typedef struct mqtt_binary mqtt_binary;

//TODO use ZALLOC later
struct conn_param {
        uint8_t         pro_ver;
        uint8_t         con_flag;
        uint16_t        keepalive_mqtt;
        uint8_t         clean_start;
        uint8_t         will_flag;
        uint8_t         will_retain;
        uint8_t         will_qos;
        struct mqtt_string      pro_name;
        struct mqtt_string      clientid;
        struct mqtt_string      will_topic;
        struct mqtt_string      will_msg;
        struct mqtt_string      username;
        struct mqtt_binary      password;
        //conn_propt    ppt;
        //mqtt_v5
        //variable header
        uint32_t        session_expiry_interval;
        uint16_t        rx_max;
        uint32_t        max_packet_size;
        uint16_t        topic_alias_max;
        uint8_t         req_resp_info;
        uint8_t         req_problem_info;
        struct mqtt_string      auth_method;
        struct mqtt_binary      auth_data;
        struct mqtt_string_pair user_property;
        //payload
        uint32_t        will_delay_interval;
        uint8_t         payload_format_indicator;
        uint32_t        msg_expiry_interval;
        struct mqtt_string      content_type;
        struct mqtt_string      resp_topic;
        struct mqtt_binary      corr_data;
        struct mqtt_string_pair payload_user_property;
};

#endif // CORE_SOCKET_H
