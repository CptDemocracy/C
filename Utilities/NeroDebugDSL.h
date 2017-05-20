/* nero is a minimalistic DSL whose only purpose is to sugarcoat your C specs.
 * It was largely inspired by the RSpec gem for Ruby.
 */
 
#ifndef NERO_DBG_DSL
#define NERO_DBG_DSL

void _setup_t_buf  (void);
void _free_t_buf   (void);
int  _rewind_t_buf (void); 
int  _write_t_buf  (const char *s);
int  _print_descr  (void); 
int  _clear_t_buf  (void);

#define describe(what) for(int _d = 0, _ = (_write_t_buf(what)); _d < 1; (void)_rewind_t_buf(), ++_d)
#define context(what)  for(int _c = 0, _ = (_write_t_buf(what)); _c < 1; (void)_rewind_t_buf(), ++_c)
#define it(what)       for(int _i = 0, _ = (_write_t_buf(what), _print_descr(), _rewind_t_buf()); _i < 1; ++_i)

#endif /* NERO_DBG_DSL */
