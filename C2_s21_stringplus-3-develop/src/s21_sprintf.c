#include "s21_string.h"

void s21_to_string_int(int x, s21_size_t *size, char *num) {
  int number = pow(10, s21_numcount_int(abs(x)) - 1);
  int count = 10;
  *size = s21_numcount_int(abs(x));
  for (s21_size_t i = 0; i < *size; i++) {
    num[i] = '0' + (abs(x) / number % count);
    number /= 10;
  }
  num[*size] = '\0';
}

void ftoa(double n, char *massive) {
  int i = 0, j = 0, sign = 0, k = 0;
  double p = 0, z = 0;
  if ((sign = n) < 0) {
    n = -n;
  }
  p = modf(n, &z);
  k = z;
  do {
    massive[i++] = (int)k % 10 + '0';
  } while ((k /= 10) > 0);
  if (sign < 0) massive[i++] = '-';
  massive[i] = '\0';
  reverse(massive);
  massive[i++] = '.';
  j = i;
  k = (int)(roundf(p * 1000000)) % 1000000;
  int count = 0;
  do {
    massive[i++] = k % 10 + '0';
    count++;
  } while ((k /= 10) >= 0 && count != 6);
  reversedot(massive, j);
  massive[i] = '\0';
}

void reverse(char s[]) {
  int i, j;
  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void reversedot(char s[], int j) {
  for (int i = s21_strlen(s) - 1; j < i; j++, i--) {
    char c = s[j];
    s[j] = s[i];
    s[i] = c;
  }
}

int print_unsigned(unsigned num, char *str) {
  char res[100] = "0";
  for (int i = 0; num; ++i) {
    int rem = num % 10;
    res[i] = rem + '0';
    num /= 10;
  }
  int count = 0;
  for (int i = s21_strlen(res) - 1; i > -1; i--) {
    str[count] = res[i];
    count++;
  }
  return count;
}

void initial_struct(struct s21_sprintf *flag) {
  flag->c = 0;
  flag->d = 0;
  flag->other = 0;
  flag->percent = 0;
  flag->plus = 0;
  flag->s = 0;
  flag->u = 0;
  flag->f = 0;
  flag->wight = 0;
}

void s21_parse_format(const char *format, struct s21_sprintf *flag) {
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    switch (format[i]) {
      case 'd':
        flag->d += 1;
        break;
      case 'f':
        flag->f += 1;
        break;
      case 'c':
        flag->c += 1;
        break;
      case 's':
        flag->s += 1;
        break;
      case 'u':
        flag->u += 1;
        break;
      case '-':
        flag->wight += 1;
        break;
      case '+':
        flag->plus += 1;
        break;
      case '%':
        flag->percent += 1;
        break;
      default:
        break;
    }
    if (format[i] == 's' || format[i] == 'd' || format[i] == 'c' ||
        format[i] == 'u' || format[i] == 'f') {
      break;
    }
  }
}

int touch_number(const char *number, char *buf, s21_size_t n,
                 struct s21_sprintf flag, int count_number, int quantity) {
  int count = 0;
  char touch[20];
  for (int i = 0; i < count_number; i++) {
    if (number[i] == '.') {
      i++;
      while (i < count_number) {
        touch[count] = number[i];
        count++;
        i++;
      }
    }
  }
  touch[count] = '\0';
  s21_size_t num_touch = s21_intnumber(touch, count, &flag);
  if (n <= num_touch) {
    char str[100];
    int new = 0;
    for (s21_size_t i = 0; i < num_touch - n; i++, new ++) {
      str[new] = '0';
    }
    str[new] = '\0';
    s21_strcat(str, buf);
    s21_strcpy(buf, str);
    quantity += new;
  }
  return quantity;
}

int s21_charnumber(const char *istr, int *count_other, char *number,
                   struct s21_sprintf *flag) {
  int count_number = 0;
  for (s21_size_t i = 0; i < s21_strlen(istr); i++) {
    if (istr[i] == 's' || istr[i] == 'd' || istr[i] == 'c' || istr[i] == 'u' ||
        istr[i] == 'f') {
      *count_other = i + 1;
      break;
    }
    if (istr[i] == '-' && flag->d != 0) {
      continue;
    } else {
      number[count_number] = istr[i];
      count_number++;
    }
  }
  number[count_number] = '\0';
  return count_number;
}

int s21_intnumber(const char *number, int count_number,
                  struct s21_sprintf *flag) {
  int num_res = 0;
  int s_pow = 0;
  int initial = 0;
  for (s21_size_t i = 0; i < s21_strlen(number); i++) {
    if (number[i] == '.') {
      count_number = i;
      break;
    }
  }
  if (number[0] == '-' || number[0] == '+' || number[0] == '.') {
    s_pow = pow(10, count_number - 2);
    initial = 1;
  } else {
    s_pow = pow(10, count_number - 1);
    initial = 0;
  }
  if ((number[0] == ' ' || number[0] == '0') && flag->d == 1) {
    s_pow = pow(10, count_number - 2);
    initial = 1;
  }
  int right = 1;
  for (int i = initial; i < count_number; i++) {
    num_res += (number[i] - '0') * s_pow / right;
    right *= 10;
  }
  return num_res;
}

int flag_d(int x, const char *number, s21_size_t num_res, char *istr,
           int quantity, char *buf) {
  s21_size_t size = 0;
  int k = 0;
  if (x < 0) {
    k = s21_numcount_int(x) + 1;
  } else {
    k = s21_numcount_int(x);
  }
  if (number[0] == ' ' && x < 0 && num_res == 0 &&
      s21_strchr(istr, '.') == NULL) {
    quantity--;
  }
  char num[k];
  s21_to_string_int(x, &size, num);
  for (s21_size_t i = 0; i < size; i++, quantity++) {
    buf[quantity] = num[i];
  }
  buf[quantity] = '\0';
  return quantity;
}

int s21_minus_plus(char *buf, const char *istr, int number_d, int quantity,
                   struct s21_sprintf *flag) {
  char str[s21_strlen(buf) + 1];
  s21_size_t count = 0;
  for (s21_size_t i = 0; i < 1; i++, count++) {
    if (istr[0] == '+') str[count] = '+';
    if (number_d < 0) str[count] = '-';
  }
  str[count] = '\0';
  s21_strcat(str, buf);
  s21_strcpy(buf, str);
  quantity += count;
  flag->plus--;
  return quantity;
}

int s21_wight(s21_size_t num_res, char *buf, int quantity) {
  char str[100];
  int count = 0;
  for (s21_size_t i = 0; i < num_res - s21_strlen(buf); i++, count++) {
    str[count] = ' ';
  }
  str[count] = '\0';
  s21_strcat(str, buf);
  s21_strcpy(buf, str);
  quantity += count;
  buf[quantity] = '\0';
  return quantity;
}

int s21_check(char *number, int quantity, s21_size_t num_res, char *buf) {
  if ((s21_strlen(number) > 0 && (number[0] != '-' && number[0] != '+') &&
       (num_res == 0) && ((s21_strlen(number) == 1 && number[0] != '0')))) {
    for (s21_size_t i = 0; i < s21_strlen(number); i++, quantity++) {
      buf[quantity] = number[i];
    }
  }
  if ((s21_strlen(number) > 1 && number[0] == '0' &&
       num_res >= s21_strlen(number))) {
    buf[quantity++] = number[0];
  }
  return quantity;
}

int check_signs(char *istr, int quantity, char *number, char *buf, int n,
                struct s21_sprintf flag, int count_number, int number_d,
                s21_size_t num_res, int count_other) {
  if (s21_strchr(istr, '.') != NULL) {
    quantity = touch_number(number, buf, n, flag, count_number, quantity);
  }
  if (istr[0] == '+' || number_d < 0) {
    quantity = s21_minus_plus(buf, istr, number_d, quantity, &flag);
  }
  if (istr[0] == '-' && num_res != 0) {
    if (num_res > s21_strlen(buf)) {
      for (s21_size_t i = s21_strlen(buf); i < num_res; i++, quantity++) {
        buf[quantity] = ' ';
      }
      buf[quantity++] = '\0';
    }
  }
  if (istr[0] != '-' && s21_strlen(buf) <= num_res && num_res != 0) {
    quantity = s21_wight(num_res, buf, quantity);
  }
  if (s21_strlen(istr) != 1) {
    for (s21_size_t i = count_other; i < s21_strlen(istr); i++, quantity++) {
      buf[quantity] = istr[i];
    }
  }
  return quantity;
}
int s21_sprintf(char *buf, const char *format, ...) {
  struct s21_sprintf flag;
  int quantity = 0;
  s21_size_t n = 0;
  int number_d = 0;
  va_list arg;
  va_start(arg, format);
  char copy_format[s21_strlen(format)];
  s21_strcpy(copy_format, format);
  buf[quantity] = '\0';
  char *istr = s21_strtok(copy_format, "%");
  while (istr != NULL) {
    initial_struct(&flag);
    s21_parse_format(istr, &flag);
    char number[100];
    int count_other = 0;
    int count_number = s21_charnumber(istr, &count_other, number, &flag);
    s21_size_t num_res = s21_intnumber(number, count_number, &flag);
    quantity = s21_check(number, quantity, num_res, buf);
    if (flag.d != 0) {
      int x = va_arg(arg, int);
      number_d = x;
      n = s21_numcount_int(abs(x));
      quantity = flag_d(x, number, num_res, istr, quantity, buf);
      flag.d--;
    }
    if (flag.c != 0) {
      char c = va_arg(arg, int);
      buf[quantity++] = c;
      buf[quantity] = '\0';
      flag.c--;
    }
    if (flag.f != 0) {
      double f = va_arg(arg, double);
      char str[100] = "";
      ftoa(f, str);
      s21_strcpy(buf, str);
      quantity += s21_strlen(str);
    }
    if (flag.s != 0) {
      char *s = va_arg(arg, char *);
      for (s21_size_t i = 0; i < s21_strlen(s); i++, quantity++) {
        buf[quantity] = s[i];
      }
      buf[quantity++] = '\0';
      flag.s--;
    }
    if (flag.u != 0) {
      unsigned u = va_arg(arg, unsigned);
      n = s21_numcount_int(u);
      char *str = (char *)malloc(sizeof(char) * 10000);
      s21_size_t uns = print_unsigned(u, str);
      for (s21_size_t i = 0; i < uns; i++, quantity++) {
        buf[quantity] = str[i];
      }
      buf[quantity] = '\0';
      flag.u--;
      free(str);
    }
    quantity = check_signs(istr, quantity, number, buf, n, flag, count_number,
                           number_d, num_res, count_other);
    istr = s21_strtok(NULL, "%");
  }
  buf[quantity] = '\0';
  va_end(arg);
  return s21_strlen(buf);
}
