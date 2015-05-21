/*
** mrb_sleep - sleep class for mruby
**
** Copyright (c) mod_mruby developers 2012-
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [ MIT license: http://www.opensource.org/licenses/mit-license.php ]
*/

#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x * 1000)
#define usleep(x) Sleep(((x) < 1000) ? 1 : ((x) / 1000))
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#include "mruby.h"
#include "mruby/numeric.h"


// Revised by Paolo Bosetti in order to mimic vanilla ruby behavior
// sleep forever is not implemented
static mrb_value mrb_f_sleep_sleep(mrb_state *mrb, mrb_value self) {
  time_t beg;
  mrb_value arg;
  mrb_float c_arg;
  useconds_t us;
  unsigned int s;
  beg = time(0);
  
  mrb_get_args(mrb, "o", &arg);
  
  if (mrb_fixnum_p(arg)) {
    sleep(mrb_fixnum(arg));
  } 
  else if (mrb_float_p(arg)) {
    c_arg = mrb_to_flo(mrb, arg);
    s = (unsigned int)c_arg;
    us = (useconds_t)((c_arg - s) * 1e6);
    if (s > 0)
      sleep(s);
    usleep(us);
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Only Fixnum or Float value");
  }
  
  return mrb_fixnum_value(time(0) - beg);
}

void mrb_mruby_sleep_gem_init(mrb_state *mrb) {
  mrb_define_method(mrb, mrb->kernel_module, "sleep", mrb_f_sleep_sleep,
                    ARGS_REQ(1));
}

void mrb_mruby_sleep_gem_final(mrb_state *mrb) {}
