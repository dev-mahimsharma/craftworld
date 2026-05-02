#ifndef KEY_MAPPING_H
#define KEY_MAPPING_H

#ifdef __CPLUSPLUS
extern "c" {
#endif

#define CW_KEY_MAP() (cw_key_mapping())

extern void cw_key_mapping(void);

#ifdef __CPLUSPLUS
}
#endif

#endif  // !KEY_MAPPING_H