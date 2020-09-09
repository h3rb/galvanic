#include "zerotypes.h"

/// Temporary buffer for int->string conversions
char tbuf[128];

#if IS_WINDOWS
#include <varargs.h>
#else
#include <stdarg.h>
#endif

#define FORMAT_STRING_SIZE 65536

void output__(const char * fmt, ...) {
    string s;
    static char FMT_buf[FORMAT_STRING_SIZE];
    va_list args;
    va_start( args, fmt );
   #if IS_WINDOWS
    vsprintf_s(FMT_buf, fmt, args);
   #else
    vsprintf(FMT_buf, fmt, args);
   #endif
    va_end(args);
    s=string(FMT_buf);
    qDebug() << s.c_str();
}

string FMT(const char*fmt, ...) {
 string s;
 static char FMT_buf[FORMAT_STRING_SIZE];
 va_list args;
 va_start( args, fmt );
#if IS_WINDOWS
 vsprintf_s(FMT_buf, fmt, args);
#else
 vsprintf(FMT_buf, fmt, args);
#endif
 va_end(args);
 s=string(FMT_buf);
 return s;
}


/// Forward declared type assocations

/// Zfloat operator= overloads for forward declared types

Zfloat& Zfloat::operator= ( const Zbyte& b   ) { value=(float)b.value; return *this; }
Zfloat& Zfloat::operator= ( const Zuint& i   ) { value=(float)i.value; return *this; }
Zfloat& Zfloat::operator= ( const Zint& i    ) { value=(float)i.value; return *this; }
Zfloat& Zfloat::operator= ( const Zdouble& d ) { value=(float)d.value; return *this; }
Zfloat& Zfloat::operator= ( const std::string& s ) { value=(float)atof(s.c_str()); return *this; }
float Zfloat::operator()( Zbyte &b )   { return value=(float)b.value; }
float Zfloat::operator()( Zuint &i )   { return value=(float)i.value; }
float Zfloat::operator()( Zint &i )    { return value=(float)i.value; }
float Zfloat::operator()( Zfloat &f )  { return value; }
float Zfloat::operator()( Zdouble &d ) { return value=(float)d.value; }
Zfloat& Zfloat::operator+= ( const Zint& i ) { value+=(float)i.value; return *this; }
Zfloat& Zfloat::operator-= ( const Zint& i ) { value-=(float)i.value; return *this; }
Zfloat& Zfloat::operator*= ( const Zint& i ) { value*=(float)i.value; return *this; }
Zfloat& Zfloat::operator/= ( const Zint& i ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( (float) i.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in /= operation!");
#endif
  value=0.0f;
  return *this;
 }
#endif
 value/=(float)i.value;
 return *this;
}

/// Zbyte operator= overloads for forward declared types

Zbyte& Zbyte::operator= ( const Zuint& i )   { value=(unsigned char)i.value; return *this; }
Zbyte& Zbyte::operator= ( const Zint& i )    { value=(unsigned char)i.value; return *this; }
Zbyte& Zbyte::operator= ( const Zfloat& f )  { value=(unsigned char)f.value; return *this; }
Zbyte& Zbyte::operator= ( const Zdouble& d ) { value=(unsigned char)d.value; return *this; }
Zbyte& Zbyte::operator= ( const std::string& s ) { value=(unsigned char)atof(s.c_str()); return *this; }
unsigned char Zbyte::operator()( Zuint &i )   { return value=(unsigned char)i.value; }
unsigned char Zbyte::operator()( Zint &i )    { return value=(unsigned char)i.value; }
unsigned char Zbyte::operator()( Zfloat &f )  { return value=(unsigned char)f.value; }
unsigned char Zbyte::operator()( Zdouble &d ) { return value=(unsigned char)d.value; }

/// Zushort operator= overloads for forward declared types

Zushort& Zushort::operator= ( const Zuint& i )   { value=(unsigned short)i.value; return *this; }
Zushort& Zushort::operator= ( const Zint& i )    { value=(unsigned short)i.value; return *this; }
Zushort& Zushort::operator= ( const Zfloat& f )  { value=(unsigned short)f.value; return *this; }
Zushort& Zushort::operator= ( const Zdouble& d ) { value=(unsigned short)d.value; return *this; }
Zushort& Zushort::operator= ( const std::string& s ) { value=(unsigned short)atof(s.c_str()); return *this; }
unsigned short Zushort::operator()( Zuint &i )   { return value=(unsigned short)i.value; }
unsigned short Zushort::operator()( Zint &i )    { return value=(unsigned short)i.value; }
unsigned short Zushort::operator()( Zfloat &f )  { return value=(unsigned short)f.value; }
unsigned short Zushort::operator()( Zdouble &d ) { return value=(unsigned short)d.value; }

/// Zuint operator= overloads for forward declared types

Zuint& Zuint::operator= ( const Zbyte& b )   { value=(unsigned int)b.value; return *this; }
Zuint& Zuint::operator= ( const Zint& i )    { value=(unsigned int)i.value; return *this; }
Zuint& Zuint::operator= ( const Zfloat& f )  { value=(unsigned int)f.value; return *this; }
Zuint& Zuint::operator= ( const Zdouble& d ) { value=(unsigned int)d.value; return *this; }
Zuint& Zuint::operator= ( const std::string& s ) { value=(unsigned int)atof(s.c_str()); return *this; }
unsigned int Zuint::operator()( Zbyte &b )   { return value=(unsigned int)b.value; }
unsigned int Zuint::operator()( Zint &i )    { return value=(unsigned int)i.value; }
unsigned int Zuint::operator()( Zfloat &f )  { return value=(unsigned int)f.value; }
unsigned int Zuint::operator()( Zdouble &d ) { return value=(unsigned int)d.value; }

/// Zint operator= overloads for forward declared types

Zint& Zint::operator= ( const Zbyte& b )   { value=(int)b.value; return *this; }
Zint& Zint::operator= ( const Zuint& i )   { value=(int)i.value; return *this; }
Zint& Zint::operator= ( const Zfloat& f )  { value=(int)f.value; return *this; }
Zint& Zint::operator= ( const Zdouble& d ) { value=(int)d.value; return *this; }
Zint& Zint::operator= ( const std::string& s ) { value=(int)atof(s.c_str()); return *this; }
int Zint::operator()( Zbyte &b )   { return (value=(int)b.value); }
int Zint::operator()( Zuint &i )   { return (value=(int)i.value); }
int Zint::operator()( Zfloat &f )  { return (value=(int)f.value); }
int Zint::operator()( Zdouble &d ) { return (value=(int)d.value); }
Zint& Zint::operator+= ( const Zfloat& f ) { value+=(int)f.value; return *this; }
Zint& Zint::operator-= ( const Zfloat& f ) { value-=(int)f.value; return *this; }
Zint& Zint::operator*= ( const Zfloat& f ) { value*=(int)f.value; return *this; }
Zint& Zint::operator/= ( const Zfloat& f ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( (int) f.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in /= operation!");
#endif
  value=0;
  return *this;
 }
#endif
 value/=(int)f.value;
 return *this;
}

/// Zdouble operator= overloads for forward declared types

Zdouble& Zdouble::operator= ( const Zbyte& b )   { value=(double)b.value; return *this; }
Zdouble& Zdouble::operator= ( const Zuint& i )   { value=(double)i.value; return *this; }
Zdouble& Zdouble::operator= ( const Zint& i )    { value=(double)i.value; return *this; }
Zdouble& Zdouble::operator= ( const Zfloat& f )  { value=(double)f.value; return *this; }
Zdouble& Zdouble::operator= ( const std::string& s ) { value=(double)atof(s.c_str()); return *this; }
double Zdouble::operator()( Zbyte &b )  { return value=(double)b.value; }
double Zdouble::operator()( Zuint &i )  { return value=(double)i.value; }
double Zdouble::operator()( Zint &i )   { return value=(double)i.value; }
double Zdouble::operator()( Zfloat &f ) { return value=(double)f.value; }

/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// start

// Mixed type operations
float operator+ ( const Zfloat& a, const Zint& b ) { return (float) b.value + a.value; }
float operator+ ( const Zint& a, const Zfloat& b ) { return (float) a.value + b.value; }
float operator* ( const Zfloat& a, const Zint& b ) { return (float) b.value * a.value; }
float operator* ( const Zint& a, const Zfloat& b ) { return (float) a.value * b.value; }

// Zfloat and itself
float operator+ ( const Zfloat& a, const Zfloat& b ) { return a.value+b.value; }
float operator- ( const Zfloat& a, const Zfloat& b ) { return a.value-b.value; }
float operator* ( const Zfloat& a, const Zfloat& b ) { return a.value*b.value; }
float operator/ ( const Zfloat& a, const Zfloat& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return a.value/b.value;
}
/* Creates C2593 for some reason...
float operator+ ( Zfloat a, Zfloat b ) { return a.value+b.value; }
float operator- ( Zfloat a, Zfloat b ) { return a.value-b.value; }
float operator* ( Zfloat a, Zfloat b ) { return a.value*b.value; }
float operator/ ( Zfloat a, Zfloat b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return a.value/b.value;
}
*/

/// Zfloat and int

// Casted int operations
float operator+ ( const Zfloat& a, int b ) { return a.value+(float)b; }
float operator- ( const Zfloat& a, int b ) { return a.value-(float)b; }
float operator* ( const Zfloat& a, int b ) { return a.value*(float)b; }
float operator/ ( const Zfloat& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return a.value/(float)b;
}
// Casted int operations reversed
float operator+ ( int b, const Zfloat& a ) { return a.value+(float)b; }
float operator- ( int b, const Zfloat& a ) { return (float)b-a.value; }
float operator* ( int b, const Zfloat& a ) { return a.value*(float)b; }
float operator/ ( int b, const Zfloat& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return (float)b/a.value;
}

/// Zfloat and float

// Float operations
float operator+ ( float b, const Zfloat& a ) { return a.value+b; }
float operator- ( float b, const Zfloat& a ) { return b-a.value; }
float operator* ( float b, const Zfloat& a ) { return a.value*b; }
float operator/ ( float b, const Zfloat& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return b/a.value;
}
// Float operations reversed
float operator+ ( const Zfloat& a, float b ) { return a.value+b; }
float operator- ( const Zfloat& a, float b ) { return a.value-b; }
float operator* ( const Zfloat& a, float b ) { return a.value*b; }
float operator/ ( const Zfloat& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return a.value/b;
}

/// Zfloat and double

// Casted double operations (leans toward double precision)
float operator+ ( double b, const Zfloat& a ) { return (float)((double)a.value+b); }
float operator- ( double b, const Zfloat& a ) { return (float)(b-(double)a.value); }
float operator* ( double b, const Zfloat& a ) { return (float)((double)a.value*b); }
float operator/ ( double b, const Zfloat& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0.0f) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return (float)(b/(double)a.value);
}
// Casted double operations reversed (leans toward double precision)
float operator+ ( const Zfloat& a, double b ) { return (float)((double)a.value+b); }
float operator- ( const Zfloat& a, double b ) { return (float)((double)a.value-b); }
float operator* ( const Zfloat& a, double b ) { return (float)((double)a.value*b); }
float operator/ ( const Zfloat& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zfloat: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return (float)((double)a.value/b);
}

// Zfloat boolean operations
bool operator>= ( const Zfloat& a, const Zfloat& b ) { return ( a.value >= b.value );    }
bool operator>= ( const Zfloat& a, const Zbyte& b ) { return ( a.value >= (float) b.value );    }
bool operator>= ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value >= b.value ); }
bool operator>= ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value >= b.value ); }
bool operator>= ( const Zfloat& a, const Zint& b )    { return ((int) a.value >= b.value ); }
bool operator>= ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value >= b.value ); }
bool operator>= ( const Zbyte& a, const Zfloat& b )   { return (a.value >= (unsigned char) b.value ); }
bool operator>= ( const Zushort& a, const Zfloat& b ) { return (a.value >= (unsigned short) b.value ); }
bool operator>= ( const Zuint& a, const Zfloat& b )   { return (a.value >= (unsigned int) b.value ); }
bool operator>= ( const Zint& a, const Zfloat& b )    { return (a.value >= (int) b.value ); }
bool operator>= ( const Zdouble& a, const Zfloat& b ) { return (a.value >= (double) b.value ); }
bool operator>= ( const Zfloat& a, int b )           { return ( (int) a.value >= b );    }
bool operator>= ( const Zfloat& a, float b )         { return ( a.value >= b );          }
bool operator>= ( const Zfloat& a, double b )        { return ( (double) a.value >= b ); }
bool operator>= ( int a, const Zfloat& b )           { return ( a >= (int) b.value );    }
bool operator>= ( float a, const Zfloat& b )         { return ( a >= b.value );          }
bool operator>= ( double a, const Zfloat& b )        { return ( a >= (double) b.value ); }
bool operator== ( const Zfloat& a, const Zbyte& b )   { return ((unsigned char) a.value == b.value ); }
bool operator== ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value == b.value ); }
bool operator== ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value == b.value ); }
bool operator== ( const Zfloat& a, const Zint& b )    { return ((int) a.value == b.value ); }
bool operator== ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value == b.value ); }
bool operator== ( const Zbyte& a, const Zfloat& b )   { return (a.value == (unsigned char) b.value ); }
bool operator== ( const Zushort& a, const Zfloat& b ) { return (a.value == (unsigned short) b.value ); }
bool operator== ( const Zuint& a, const Zfloat& b )   { return (a.value == (unsigned int) b.value ); }
bool operator== ( const Zint& a, const Zfloat& b )    { return (a.value == (int) b.value ); }
bool operator== ( const Zdouble& a, const Zfloat& b ) { return (a.value == (double) b.value ); }
bool operator== ( const Zfloat& a, const Zfloat& b ) { return ( a.value == b.value );    }
bool operator== ( const Zfloat& a, int b )           { return ( (int) a.value == b );    }
bool operator== ( const Zfloat& a, float b )         { return ( a.value == b );          }
bool operator== ( const Zfloat& a, double b )        { return ( (double) a.value == b ); }
bool operator== ( int a, const Zfloat& b )           { return ( a == (int) b.value );    }
bool operator== ( float a, const Zfloat& b )         { return ( a == b.value );          }
bool operator== ( double a, const Zfloat& b )        { return ( a == (double) b.value ); }
bool operator!= ( const Zfloat& a, const Zfloat& b ) { return ( a.value != b.value );    }
bool operator!= ( const Zfloat& a, const Zbyte& b ) { return ( a.value != (float)b.value );    }
bool operator!= ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value != b.value ); }
bool operator!= ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value != b.value ); }
bool operator!= ( const Zfloat& a, const Zint& b )    { return ((int) a.value != b.value ); }
bool operator!= ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value != b.value ); }
bool operator!= ( const Zbyte& a, const Zfloat& b )   { return (a.value != (unsigned char) b.value ); }
bool operator!= ( const Zushort& a, const Zfloat& b ) { return (a.value != (unsigned short) b.value ); }
bool operator!= ( const Zuint& a, const unsigned int b )  { return (a.value != b ); }
bool operator!= ( const Zuint& a, const int b )       { return (a.value != (unsigned int) b ); }
bool operator!= ( const Zuint& a, const Zfloat& b )   { return (a.value != (unsigned int) b.value ); }
bool operator!= ( const Zint& a, const Zfloat& b )    { return (a.value != (int) b.value ); }
bool operator!= ( const Zdouble& a, const Zfloat& b ) { return (a.value != (double) b.value ); }
bool operator!= ( const Zfloat& a, int b )           { return ( (int) a.value != b );    }
bool operator!= ( const Zfloat& a, float b )         { return ( a.value != b );          }
bool operator!= ( const Zfloat& a, double b )        { return ( (double) a.value != b ); }
bool operator!= ( int a, const Zfloat& b )           { return ( a != (int) b.value );    }
bool operator!= ( float a, const Zfloat& b )         { return ( a != b.value );          }
bool operator!= ( double a, const Zfloat& b )        { return ( a != (double) b.value ); }
bool operator<= ( const Zfloat& a, const Zfloat& b ) { return ( a.value <= b.value );    }
bool operator<= ( const Zfloat& a, const Zbyte& b )  { return ( a.value <= (float) b.value ); }
bool operator<= ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value <= b.value ); }
bool operator<= ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value <= b.value ); }
bool operator<= ( const Zfloat& a, const Zint& b )    { return ((int) a.value <= b.value ); }
bool operator<= ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value <= b.value ); }
bool operator<= ( const Zbyte& a, const Zfloat& b )   { return (a.value <= (unsigned char) b.value ); }
bool operator<= ( const Zushort& a, const Zfloat& b ) { return (a.value <= (unsigned short) b.value ); }
bool operator<= ( const Zuint& a, const Zfloat& b )   { return (a.value <= (unsigned int) b.value ); }
bool operator<= ( const Zint& a, const Zfloat& b )    { return (a.value <= (int) b.value ); }
bool operator<= ( const Zdouble& a, const Zfloat& b ) { return (a.value <= (double) b.value ); }
bool operator<= ( const Zfloat& a, int b )           { return ( (int) a.value <= b );    }
bool operator<= ( const Zfloat& a, float b )         { return ( a.value <= b );          }
bool operator<= ( const Zfloat& a, double b )        { return ( (double) a.value <= b ); }
bool operator<= ( int a, const Zfloat& b )           { return ( a <= (int) b.value );    }
bool operator<= ( float a, const Zfloat& b )         { return ( a <= b.value );          }
bool operator<= ( double a, const Zfloat& b )        { return ( a <= (double) b.value ); }
bool operator> ( const Zfloat& a, const Zfloat& b )  { return ( a.value > b.value );    }
bool operator> ( const Zfloat& a, const Zbyte& b )   { return ( a.value > (float) b.value ); }
bool operator> ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value > b.value ); }
bool operator> ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value > b.value ); }
bool operator> ( const Zfloat& a, const Zint& b )    { return ((int) a.value > b.value ); }
bool operator> ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value > b.value ); }
bool operator> ( const Zbyte& a, const Zfloat& b )   { return (a.value > (unsigned char) b.value ); }
bool operator> ( const Zushort& a, const Zfloat& b ) { return (a.value > (unsigned short) b.value ); }
bool operator> ( const Zuint& a, const Zfloat& b )   { return (a.value > (unsigned int) b.value ); }
bool operator> ( const Zint& a, const Zfloat& b )    { return (a.value > (int) b.value ); }
bool operator> ( const Zdouble& a, const Zfloat& b ) { return (a.value > (double) b.value ); }
bool operator> ( const Zfloat& a, int b )            { return ( (int) a.value > b );    }
bool operator> ( const Zfloat& a, float b )          { return ( a.value > b );          }
bool operator> ( const Zfloat& a, double b )         { return ( (double) a.value > b ); }
bool operator> ( int a, const Zfloat& b )            { return ( a > (int) b.value );    }
bool operator> ( float a, const Zfloat& b )          { return ( a > b.value );          }
bool operator> ( double a, const Zfloat& b )         { return ( a > (double) b.value ); }
bool operator< ( const Zfloat& a, const Zfloat& b )  { return ( a.value < b.value );    }
bool operator< ( const Zfloat& a, const Zbyte& b )   { return ( a.value < (float) b.value ); }
bool operator< ( const Zfloat& a, const Zushort& b ) { return ((unsigned short) a.value < b.value ); }
bool operator< ( const Zfloat& a, const Zuint& b )   { return ((unsigned int) a.value < b.value ); }
bool operator< ( const Zfloat& a, const Zint& b )    { return ((int) a.value < b.value ); }
bool operator< ( const Zfloat& a, const Zdouble& b ) { return ((double) a.value < b.value ); }
bool operator< ( const Zbyte& a, const Zfloat& b )   { return (a.value < (unsigned char) b.value ); }
bool operator< ( const Zushort& a, const Zfloat& b ) { return (a.value < (unsigned short) b.value ); }
bool operator< ( const Zuint& a, const Zfloat& b )   { return (a.value < (unsigned int) b.value ); }
bool operator< ( const Zint& a, const Zfloat& b )    { return (a.value < (int) b.value ); }
bool operator< ( const Zdouble& a, const Zfloat& b ) { return (a.value < (double) b.value ); }
bool operator< ( const Zfloat& a, int b )            { return ( (int) a.value < b );    }
bool operator< ( const Zfloat& a, float b )          { return ( a.value < b );          }
bool operator< ( const Zfloat& a, double b )         { return ( (double) a.value < b ); }
bool operator< ( int a, const Zfloat& b )            { return ( a < (int) b.value );    }
bool operator< ( float a, const Zfloat& b )          { return ( a < b.value );          }
bool operator< ( double a, const Zfloat& b )         { return ( a < (double) b.value ); }

/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zbyte ////////////////////////////////////////////////////////////////////////////////////////// start

unsigned char operator+ ( const Zbyte& a, const Zbyte& b ) { return a.value+b.value; }
unsigned char operator- ( const Zbyte& a, const Zbyte& b ) { return a.value-b.value; }
unsigned char operator* ( const Zbyte& a, const Zbyte& b ) { return a.value*b.value; }
unsigned char operator/ ( const Zbyte& a, const Zbyte& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}
unsigned char operator+ ( Zbyte a, Zbyte b ) { return a.value+b.value; }
unsigned char operator- ( Zbyte a, Zbyte b ) { return a.value-b.value; }
unsigned char operator* ( Zbyte a, Zbyte b ) { return a.value*b.value; }
unsigned char operator/ ( Zbyte a, Zbyte b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}

/// Zbyte and uint

// Casted int operations
unsigned char operator+ ( const Zbyte& a, unsigned char b ) {
 return a.value+b;
}
unsigned char operator- ( const Zbyte& a, unsigned char b ) {
 return a.value-b;
}
unsigned char operator* ( const Zbyte& a, unsigned char b ) {
 return a.value*b;
}
unsigned char operator/ ( const Zbyte& a, unsigned char b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b;
}
// Casted int operations reversed
unsigned char operator+ ( unsigned char b, const Zbyte& a ) {
 return a.value+b;
}
unsigned char operator- ( unsigned char b, const Zbyte& a ) {
 return b-a.value;
}
unsigned char operator* ( unsigned char b, const Zbyte& a ) {
 return a.value*b;
}
unsigned char operator/ ( unsigned char b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return b/a.value;
}

/// Zuint and int

// Casted int operations
unsigned char operator+ ( const Zbyte& a, int b ) {
 return a.value+(unsigned char) b;
}
unsigned char operator- ( const Zbyte& a, int b ) {
 return a.value-(unsigned char) b;
}
unsigned char operator* ( const Zbyte& a, int b ) {
 return a.value*(unsigned char) b;
}
unsigned char operator/ ( const Zbyte& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/(unsigned char) b;
}
// Casted int operations reversed
unsigned char operator+ ( int b, const Zbyte& a ) {
 return a.value+(unsigned char) b;
}
unsigned char operator- ( int b, const Zbyte& a ) {
 return (unsigned char) b-a.value;
}
unsigned char operator* ( int b, const Zbyte& a ) {
 return a.value*(unsigned char) b;
}
unsigned char operator/ ( int b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned char) b/a.value;
}

/// Zbyte and float

// Float operations (leans toward float precision)
unsigned char operator+ ( float b, const Zbyte& a ) {
 return (unsigned char)((float)a.value+b);
}
unsigned char operator- ( float b, const Zbyte& a ) {
 return (unsigned char)(b-(float)a.value);
}
unsigned char operator* ( float b, const Zbyte& a ) {
 return (unsigned char)((float)a.value*b);
}
unsigned char operator/ ( float b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned char)(b/(float)a.value);
}
// Float operations reversed (leans toward float precision)
unsigned char operator+ ( const Zbyte& a, float b ) {
 return (unsigned char)((float)a.value+b);
}
unsigned char operator- ( const Zbyte& a, float b ) {
 return (unsigned char)((float)a.value-b);
}
unsigned char operator* ( const Zbyte& a, float b ) {
 return (unsigned char)((float)a.value*b);
}
unsigned char operator/ ( const Zbyte& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif

 return (unsigned char)((float)a.value/b);
}

/// Zbyte and double

// Casted double operations (leans toward double precision)
unsigned char operator+ ( double b, const Zbyte& a ) {
 return (unsigned char)((double)a.value+b);
}
unsigned char operator- ( double b, const Zbyte& a ) {
 return (unsigned char)(b-(double)a.value);
}
unsigned char operator* ( double b, const Zbyte& a ) {
 return (unsigned char)((double)a.value*b);
}
unsigned char operator/ ( double b, const Zbyte& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned char)(b/(double)a.value);
}
// Casted double operations reversed (leans toward double precision)
unsigned char operator+ ( const Zbyte& a, double b ) {
 return (unsigned char)((double)a.value+b);
}
unsigned char operator- ( const Zbyte& a, double b ) {
 return (unsigned char)((double)a.value-b);
}
unsigned char operator* ( const Zbyte& a, double b ) {
 return (unsigned char)((double)a.value*b);
}
unsigned char operator/ ( const Zbyte& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned char)((double)a.value/b);
}


// Boolean operations
bool operator>= ( const Zbyte& a, const Zbyte& b ) { return ( a.value >= b.value );    }
bool operator>= ( const Zbyte& a, int b )            { return ( a.value >= (unsigned char) b ); }
bool operator>= ( const Zbyte& a, float b )          { return ( a.value >= (unsigned char) b ); }
bool operator>= ( const Zbyte& a, double b )         { return ( a.value >= (unsigned char) b ); }
bool operator>= ( int a, const Zbyte& b )            { return ( (unsigned char) a >= b.value ); }
bool operator>= ( float a, const Zbyte& b )          { return ( (unsigned char) a >= b.value ); }
bool operator>= ( double a, const Zbyte& b )         { return ( (unsigned char) a >= b.value ); }
bool operator== ( const Zbyte& a, const Zbyte& b ) { return ( a.value == b.value );    }
bool operator== ( const Zbyte& a, int b )            { return ( a.value == (unsigned char) b ); }
bool operator== ( const Zbyte& a, float b )          { return ( a.value == (unsigned char) b ); }
bool operator== ( const Zbyte& a, double b )         { return ( a.value == (unsigned char) b ); }
bool operator== ( int a, const Zbyte& b )            { return ( (unsigned char) a == b.value ); }
bool operator== ( float a, const Zbyte& b )          { return ( (unsigned char) a == b.value ); }
bool operator== ( double a, const Zbyte& b )         { return ( (unsigned char) a == b.value ); }
bool operator!= ( const Zbyte& a, const Zbyte& b ) { return ( a.value != b.value );    }
bool operator!= ( const Zbyte& a, int b )            { return ( a.value != (unsigned char) b ); }
bool operator!= ( const Zbyte& a, float b )          { return ( a.value != (unsigned char) b ); }
bool operator!= ( const Zbyte& a, double b )         { return ( a.value != (unsigned char) b ); }
bool operator!= ( int a, const Zbyte& b )            { return ( (unsigned char) a != b.value ); }
bool operator!= ( float a, const Zbyte& b )          { return ( (unsigned char) a != b.value ); }
bool operator!= ( double a, const Zbyte& b )         { return ( (unsigned char) a != b.value ); }
bool operator<= ( const Zbyte& a, const Zbyte& b ) { return ( a.value <= b.value );    }
bool operator<= ( const Zbyte& a, int b )            { return ( a.value <= (unsigned char) b ); }
bool operator<= ( const Zbyte& a, float b )          { return ( a.value <= (unsigned char) b ); }
bool operator<= ( const Zbyte& a, double b )         { return ( a.value <= (unsigned char) b ); }
bool operator<= ( int a, const Zbyte& b )            { return ( (unsigned char) a <= b.value ); }
bool operator<= ( float a, const Zbyte& b )          { return ( (unsigned char) a <= b.value ); }
bool operator<= ( double a, const Zbyte& b )         { return ( (unsigned char) a <= b.value ); }
bool operator> ( const Zbyte& a, const Zbyte& b )  { return ( a.value > b.value );    }
bool operator> ( const Zbyte& a, int b )             { return ( a.value > (unsigned char) b ); }
bool operator> ( const Zbyte& a, float b )           { return ( a.value > (unsigned char) b ); }
bool operator> ( const Zbyte& a, double b )          { return ( a.value > (unsigned char) b ); }
bool operator> ( int a, const Zbyte& b )             { return ( (unsigned char) a > b.value ); }
bool operator> ( float a, const Zbyte& b )           { return ( (unsigned char) a > b.value ); }
bool operator> ( double a, const Zbyte& b )          { return ( (unsigned char) a > b.value ); }
bool operator< ( const Zbyte& a, const Zbyte& b )  { return ( a.value < b.value );    }
bool operator< ( const Zbyte& a, int b )             { return ( a.value < (unsigned char) b ); }
bool operator< ( const Zbyte& a, float b )           { return ( a.value < (unsigned char) b ); }
bool operator< ( const Zbyte& a, double b )          { return ( a.value < (unsigned char) b ); }
bool operator< ( int a, const Zbyte& b )             { return ( (unsigned char) a < b.value ); }
bool operator< ( float a, const Zbyte& b )           { return ( (unsigned char) a < b.value ); }
bool operator< ( double a, const Zbyte& b )          { return ( (unsigned char) a < b.value ); }

/// Zbyte ////////////////////////////////////////////////////////////////////////////////////////// end


/// Zushort ////////////////////////////////////////////////////////////////////////////////////////// start

unsigned short operator+ ( const Zushort& a, const Zushort& b ) { return a.value+b.value; }
unsigned short operator- ( const Zushort& a, const Zushort& b ) { return a.value-b.value; }
unsigned short operator* ( const Zushort& a, const Zushort& b ) { return a.value*b.value; }
unsigned short operator/ ( const Zushort& a, const Zushort& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}
unsigned short operator+ ( Zushort a, Zushort b ) { return a.value+b.value; }
unsigned short operator- ( Zushort a, Zushort b ) { return a.value-b.value; }
unsigned short operator* ( Zushort a, Zushort b ) { return a.value*b.value; }
unsigned short operator/ ( Zushort a, Zushort b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}

unsigned short operator+ ( const Zushort& a, unsigned char b ) { return a.value+b; }
unsigned short operator- ( const Zushort& a, unsigned char b ) { return a.value-b; }
unsigned short operator* ( const Zushort& a, unsigned char b ) { return a.value*b; }
unsigned short operator/ ( const Zushort& a, unsigned char b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b;
}
unsigned short operator+ ( unsigned char b, const Zushort& a ) { return b+a.value; }
unsigned short operator- ( unsigned char b, const Zushort& a ) { return b-a.value; }
unsigned short operator* ( unsigned char b, const Zushort& a ) { return b*a.value; }
unsigned short operator/ ( unsigned char b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return b/a.value;
}

/// Zbyte and uint

// Casted int operations
unsigned short operator+ ( const Zushort& a, unsigned short b ) {
 return a.value+b;
}
unsigned short operator- ( const Zushort& a, unsigned short b ) {
 return a.value-b;
}
unsigned short operator* ( const Zushort& a, unsigned short b ) {
 return a.value*b;
}
unsigned short operator/ ( const Zushort& a, unsigned short b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b;
}
// Casted int operations reversed
unsigned short operator+ ( unsigned short b, const Zushort& a ) {
 return a.value+b;
}
unsigned short operator- ( unsigned short b, const Zushort& a ) {
 return b-a.value;
}
unsigned short operator* ( unsigned short b, const Zushort& a ) {
 return a.value*b;
}
unsigned short operator/ ( unsigned short b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return b/a.value;
}

/// Zushort and int

// Casted int operations
unsigned short operator+ ( const Zushort& a, int b ) {
 return a.value+(unsigned short) b;
}
unsigned short operator- ( const Zushort& a, int b ) {
 return a.value-(unsigned short) b;
}
unsigned short operator* ( const Zushort& a, int b ) {
 return a.value*(unsigned short) b;
}
unsigned short operator/ ( const Zushort& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/(unsigned short) b;
}
// Casted int operations reversed
unsigned short operator+ ( int b, const Zushort& a ) {
 return a.value+(unsigned short) b;
}
unsigned short operator- ( int b, const Zushort& a ) {
 return (unsigned short) b-a.value;
}
unsigned short operator* ( int b, const Zushort& a ) {
 return a.value*(unsigned short) b;
}
unsigned short operator/ ( int b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned short) b/a.value;
}

/// Zbyte and float

// Float operations (leans toward float precision)
unsigned short operator+ ( float b, const Zushort& a ) {
 return (unsigned short)((float)a.value+b);
}
unsigned short operator- ( float b, const Zushort& a ) {
 return (unsigned short)(b-(float)a.value);
}
unsigned short operator* ( float b, const Zushort& a ) {
 return (unsigned short)((float)a.value*b);
}
unsigned short operator/ ( float b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned char)(b/(float)a.value);
}
// Float operations reversed (leans toward float precision)
unsigned short operator+ ( const Zushort& a, float b ) {
 return (unsigned short)((float)a.value+b);
}
unsigned short operator- ( const Zushort& a, float b ) {
 return (unsigned short)((float)a.value-b);
}
unsigned short operator* ( const Zushort& a, float b ) {
 return (unsigned short)((float)a.value*b);
}
unsigned short operator/ ( const Zushort& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif

 return (unsigned short)((float)a.value/b);
}

/// Zbyte and double

// Casted double operations (leans toward double precision)
unsigned short operator+ ( double b, const Zushort& a ) {
 return (unsigned short)((double)a.value+b);
}
unsigned short operator- ( double b, const Zushort& a ) {
 return (unsigned short)(b-(double)a.value);
}
unsigned short operator* ( double b, const Zushort& a ) {
 return (unsigned short)((double)a.value*b);
}
unsigned short operator/ ( double b, const Zushort& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zushort: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned short)(b/(double)a.value);
}
// Casted double operations reversed (leans toward double precision)
unsigned short operator+ ( const Zushort& a, double b ) {
 return (unsigned short)((double)a.value+b);
}
unsigned short operator- ( const Zushort& a, double b ) {
 return (unsigned short)((double)a.value-b);
}
unsigned short operator* ( const Zushort& a, double b ) {
 return (unsigned short)((double)a.value*b);
}
unsigned short operator/ ( const Zushort& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zbyte: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned short)((double)a.value/b);
}

/// Zushort ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zint ////////////////////////////////////////////////////////////////////////////////////////// start

int operator+ ( const Zint& a, const Zint& b ) { return a.value+b.value; }
int operator- ( const Zint& a, const Zint& b ) { return a.value-b.value; }
int operator* ( const Zint& a, const Zint& b ) { return a.value*b.value; }
int operator/ ( const Zint& a, const Zint& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}
/* Creates C2593 for some reason...
int operator+ ( Zint a, Zint b ) { return a.value+b.value; }
int operator- ( Zint a, Zint b ) { return a.value-b.value; }
int operator* ( Zint a, Zint b ) { return a.value*b.value; }
int operator/ ( Zint a, Zint b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}
*/

/// Zint and int

// Casted int operations
int operator+ ( const Zint& a, int b ) { return a.value+b; }
int operator- ( const Zint& a, int b ) { return a.value-b; }
int operator* ( const Zint& a, int b ) { return a.value*b; }
int operator/ ( const Zint& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b;
}
int operator% ( const Zint& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: modulo by zero in %% operation!");
#endif
  return 0;
 }
#endif
 return a.value%b;
}
// Casted int operations reversed
int operator+ ( int b, const Zint& a ) { return a.value+b; }
int operator- ( int b, const Zint& a ) { return b-a.value; }
int operator* ( int b, const Zint& a ) { return a.value*b; }
int operator/ ( int b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return b/a.value;
}
int operator% ( int b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: modulo by zero in %% operation!");
#endif
  return 0;
 }
#endif
 return b%a.value;
}

/// Zint and float

// Float operations (leans toward float precision)
int operator+ ( float b, const Zint& a ) { return (int)((float)a.value+b); }
int operator- ( float b, const Zint& a ) { return (int)(b-(float)a.value); }
int operator* ( float b, const Zint& a ) { return (int)((float)a.value*b); }
int operator/ ( float b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (int)(b/(float)a.value);
}
// Float operations reversed (leans toward float precision)
int operator+ ( const Zint& a, float b ) { return (int)((float)a.value+b); }
int operator- ( const Zint& a, float b ) { return (int)((float)a.value-b); }
int operator* ( const Zint& a, float b ) { return (int)((float)a.value*b); }
int operator/ ( const Zint& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif

 return (int)((float)a.value/b);
}

/// Zint and double

// Casted double operations (leans toward double precision)
int operator+ ( double b, const Zint& a ) { return (int)((double)a.value+b); }
int operator- ( double b, const Zint& a ) { return (int)(b-(double)a.value); }
int operator* ( double b, const Zint& a ) { return (int)((double)a.value*b); }
int operator/ ( double b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (int)(b/(double)a.value);
}
// Casted double operations reversed (leans toward double precision)
int operator+ ( const Zint& a, double b ) { return (int)((double)a.value+b); }
int operator- ( const Zint& a, double b ) { return (int)((double)a.value-b); }
int operator* ( const Zint& a, double b ) { return (int)((double)a.value*b); }
int operator/ ( const Zint& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (int)((double)a.value/b);
}

// Modulo

int operator% ( const Zint& b, const Zint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zint: modulo by zero in %% operation!");
#endif
  return 0;
 }
#endif
 return b.value%a.value;
}

// Zint boolean operations
bool operator>= ( const Zint& a, const Zint& b ) { return ( a.value >= b.value ); }
bool operator>= ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value >= b ); }
bool operator>= ( const Zint& a, int b )         { return ( a.value >= b );       }
bool operator>= ( const Zint& a, float b )       { return ( a.value >= (int) b ); }
bool operator>= ( const Zint& a, double b )      { return ( a.value >= (int) b ); }
bool operator>= ( unsigned int a, const Zint& b ) { return ( a >= (unsigned int) b.value ); }
bool operator>= ( int a, const Zint& b )         { return ( a >= b.value );       }
bool operator>= ( float a, const Zint& b )       { return ( (int) a >= b.value ); }
bool operator>= ( double a, const Zint& b )      { return ( (int) a >= b.value ); }
bool operator== ( const Zint& a, const Zbyte& b )   { return ((unsigned char) a.value == b.value ); }
bool operator== ( const Zint& a, const Zushort& b ) { return ((unsigned short) a.value == b.value ); }
bool operator== ( const Zint& a, const Zuint& b )   { return ((unsigned int) a.value == b.value ); }
bool operator== ( const Zint& a, const Zdouble& b ) { return ((double) a.value == b.value ); }
bool operator== ( const Zbyte& a, const Zint& b )   { return (a.value == (unsigned char) b.value ); }
bool operator== ( const Zushort& a, const Zint& b ) { return (a.value == (unsigned short) b.value ); }
bool operator== ( const Zuint& a, const Zint& b )   { return (a.value == (unsigned int) b.value ); }
bool operator== ( const Zdouble& a, const Zint& b ) { return (a.value == (double) b.value ); }
bool operator== ( const Zint& a, const Zint& b ) { return ( a.value == b.value ); }
bool operator== ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value >= b ); }
bool operator== ( const Zint& a, int b )         { return ( a.value == b );       }
bool operator== ( const Zint& a, float b )       { return ( a.value == (int) b ); }
bool operator== ( const Zint& a, double b )      { return ( a.value == (int) b ); }
bool operator== ( unsigned int a, const Zint& b ) { return ( a == (unsigned int) b.value ); }
bool operator== ( int a, const Zint& b )         { return ( a == b.value );       }
bool operator== ( float a, const Zint& b )       { return ( (int) a == b.value ); }
bool operator== ( double a, const Zint& b )      { return ( (int) a == b.value ); }
bool operator!= ( const Zint& a, const Zint& b ) { return ( a.value != b.value ); }
bool operator!= ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value != b ); }
bool operator!= ( const Zint& a, int b )         { return ( a.value != b );       }
bool operator!= ( const Zint& a, float b )       { return ( a.value != (int) b ); }
bool operator!= ( const Zint& a, double b )      { return ( a.value != (int) b ); }
bool operator!= ( unsigned int a, const Zint& b ) { return ( a != (unsigned int) b.value ); }
bool operator!= ( int a, const Zint& b )         { return ( a != b.value );       }
bool operator!= ( float a, const Zint& b )       { return ( (int) a != b.value ); }
bool operator!= ( double a, const Zint& b )      { return ( (int) a != b.value ); }
bool operator<= ( const Zint& a, const Zint& b ) { return ( a.value <= b.value ); }
bool operator<= ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value <= b ); }
bool operator<= ( const Zint& a, int b )         { return ( a.value <= b );       }
bool operator<= ( const Zint& a, float b )       { return ( a.value <= (int) b ); }
bool operator<= ( const Zint& a, double b )      { return ( a.value <= (int) b ); }
bool operator<= ( unsigned int a, const Zint& b ) { return ( a <= (unsigned int) b.value ); }
bool operator<= ( int a, const Zint& b )         { return ( a <= b.value );       }
bool operator<= ( float a, const Zint& b )       { return ( (int) a <= b.value ); }
bool operator<= ( double a, const Zint& b )      { return ( (int) a <= b.value ); }
bool operator> ( const Zint& a, const Zint& b )  { return ( a.value > b.value ); }
bool operator> ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value > b ); }
bool operator> ( const Zint& a, int b )          { return ( a.value > b );       }
bool operator> ( const Zint& a, float b )        { return ( a.value > (int) b ); }
bool operator> ( const Zint& a, double b )       { return ( a.value > (int) b ); }
bool operator> ( unsigned int a, const Zint& b ) { return ( a > (unsigned int) b.value ); }
bool operator> ( int a, const Zint& b )          { return ( a > b.value );       }
bool operator> ( float a, const Zint& b )        { return ( (int) a > b.value ); }
bool operator> ( double a, const Zint& b )       { return ( (int) a > b.value ); }
bool operator< ( const Zint& a, const Zint& b )  { return ( a.value < b.value ); }
bool operator< ( const Zint& a, unsigned int b ) { return ( (unsigned int) a.value < b ); }
bool operator< ( const Zint& a, int b )          { return ( a.value < b );       }
bool operator< ( const Zint& a, float b )        { return ( a.value < (int) b ); }
bool operator< ( const Zint& a, double b )       { return ( a.value < (int) b ); }
bool operator< ( unsigned int a, const Zint& b ) { return ( a < (unsigned int) b.value ); }
bool operator< ( int a, const Zint& b )          { return ( a < b.value );       }
bool operator< ( float a, const Zint& b )        { return ( (int) a < b.value ); }
bool operator< ( double a, const Zint& b )       { return ( (int) a < b.value ); }

/// Zint ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zuint ////////////////////////////////////////////////////////////////////////////////////////// start

unsigned int operator+ ( const Zuint& a, const Zuint& b ) {
 return a.value+b.value;
}
unsigned int operator- ( const Zuint& a, const Zuint& b ) {
 return a.value-b.value;
}
unsigned int operator* ( const Zuint& a, const Zuint& b ) {
 return a.value*b.value;
}
unsigned int operator/ ( const Zuint& a, const Zuint& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b.value;
}

/// Zuint and uint

// Casted int operations
unsigned int operator+ ( const Zuint& a, unsigned int b ) {
 return a.value+b;
}
unsigned int operator- ( const Zuint& a, unsigned int b ) {
 return a.value-b;
}
unsigned int operator* ( const Zuint& a, unsigned int b ) {
 return a.value*b;
}
unsigned int operator/ ( const Zuint& a, unsigned int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/b;
}
bool operator< ( unsigned int a, const Zuint& b ) { return ( a < b.value ); }
// Casted int operations reversed
unsigned int operator+ ( unsigned int b, const Zuint& a ) {
 return a.value+b;
}
unsigned int operator- ( unsigned int b, const Zuint& a ) {
 return b-a.value;
}
unsigned int operator* ( unsigned int b, const Zuint& a ) {
 return a.value*b;
}
unsigned int operator/ ( unsigned int b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return b/a.value;
}

/// Zuint and int

// Casted int operations
unsigned int operator+ ( const Zuint& a, int b ) {
 return a.value+(unsigned int) b;
}
unsigned int operator- ( const Zuint& a, int b ) {
 return a.value-(unsigned int) b;
}
unsigned int operator* ( const Zuint& a, int b ) {
 return a.value*(unsigned int) b;
}
unsigned int operator/ ( const Zuint& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return a.value/(unsigned int) b;
}
// Casted int operations reversed
unsigned int operator+ ( int b, const Zuint& a ) {
 return a.value+(unsigned int) b;
}
unsigned int operator- ( int b, const Zuint& a ) {
 return (unsigned int) b-a.value;
}
unsigned int operator* ( int b, const Zuint& a ) {
 return a.value*(unsigned int) b;
}
unsigned int operator/ ( int b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned int) b/a.value;
}

/// Zuint and float

// Float operations (leans toward float precision)
unsigned int operator+ ( float b, const Zuint& a ) {
 return (unsigned int)((float)a.value+b);
}
unsigned int operator- ( float b, const Zuint& a ) {
 return (unsigned int)(b-(float)a.value);
}
unsigned int operator* ( float b, const Zuint& a ) {
 return (unsigned int)((float)a.value*b);
}
unsigned int operator/ ( float b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned int)(b/(float)a.value);
}
// Float operations reversed (leans toward float precision)
unsigned int operator+ ( const Zuint& a, float b ) {
 return (unsigned int)((float)a.value+b);
}
unsigned int operator- ( const Zuint& a, float b ) {
 return (unsigned int)((float)a.value-b);
}
unsigned int operator* ( const Zuint& a, float b ) {
 return (unsigned int)((float)a.value*b);
}
unsigned int operator/ ( const Zuint& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif

 return (unsigned int)((float)a.value/b);
}

/// Zuint and double

// Casted double operations (leans toward double precision)
unsigned int operator+ ( double b, const Zuint& a ) {
 return (unsigned int)((double)a.value+b);
}
unsigned int operator- ( double b, const Zuint& a ) {
 return (unsigned int)(b-(double)a.value);
}
unsigned int operator* ( double b, const Zuint& a ) {
 return (unsigned int)((double)a.value*b);
}
unsigned int operator/ ( double b, const Zuint& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned int)(b/(double)a.value);
}
// Casted double operations reversed (leans toward double precision)
unsigned int operator+ ( const Zuint& a, double b ) {
 return (unsigned int)((double)a.value+b);
}
unsigned int operator- ( const Zuint& a, double b ) {
 return (unsigned int)((double)a.value-b);
}
unsigned int operator* ( const Zuint& a, double b ) {
 return (unsigned int)((double)a.value*b);
}
unsigned int operator/ ( const Zuint& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zuint: divide by zero in / operation!");
#endif
  return 0;
 }
#endif
 return (unsigned int)((double)a.value/b);
}

/// Zuint ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zdouble ////////////////////////////////////////////////////////////////////////////////////////// start

// Mixed type operations
double operator+ ( const Zdouble& a, const Zfloat& b ) { return a.value + (double) b.value; }
double operator+ ( const Zfloat& a, const Zdouble& b ) { return (double) a.value + b.value; }
double operator+ ( const Zdouble& a, const Zint& b )   { return a.value + (double) b.value; }
double operator+ ( const Zint& a, const Zdouble& b )   { return (double) a.value + b.value; }
double operator* ( const Zdouble& a, const Zfloat& b ) { return a.value * (double) b.value; }
double operator* ( const Zfloat& a, const Zdouble& b ) { return (double) a.value * b.value; }
double operator* ( const Zdouble& a, const Zint& b )   { return a.value * (double) b.value; }
double operator* ( const Zint& a, const Zdouble& b )   { return (double) a.value * b.value; }
// Zdouble and itself
double operator+ ( const Zdouble& a, const Zdouble& b ) { return a.value+b.value; }
double operator- ( const Zdouble& a, const Zdouble& b ) { return a.value-b.value; }
double operator* ( const Zdouble& a, const Zdouble& b ) { return a.value*b.value; }
double operator/ ( const Zdouble& a, const Zdouble& b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return a.value/b.value;
}
/* Creates C2593 for some reason...
double operator+ ( Zdouble a, Zdouble b ) { return a.value+b.value; }
double operator- ( Zdouble a, Zdouble b ) { return a.value-b.value; }
double operator* ( Zdouble a, Zdouble b ) { return a.value*b.value; }
double operator/ ( Zdouble a, Zdouble b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b.value == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0f;
 }
#endif
 return a.value/b.value;
}
*/

/// Zdouble and int

// Casted int operations (leans toward double precision)
double operator+ ( const Zdouble& a, int b ) { return a.value+(double)b; }
double operator- ( const Zdouble& a, int b ) { return a.value-(double)b; }
double operator* ( const Zdouble& a, int b ) { return a.value*(double)b; }
double operator/ ( const Zdouble& a, int b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0;
 }
#endif
 return a.value/(double)b;
}
// Casted int operations reversed (leans toward double precision)
double operator+ ( int b, const Zdouble& a ) { return a.value+(double)b; }
double operator- ( int b, const Zdouble& a ) { return (double)b-a.value; }
double operator* ( int b, const Zdouble& a ) { return a.value*(double)b; }
double operator/ ( int b, const Zdouble& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0;
 }
#endif
 return (double)b/a.value;
}

/// Zdouble and float

// Float operations (leans toward float precision)
double operator+ ( float b, const Zdouble& a ) { return a.value+(double)b; }
double operator- ( float b, const Zdouble& a ) { return (double)b-a.value; }
double operator* ( float b, const Zdouble& a ) { return a.value*(double)b; }
double operator/ ( float b, const Zdouble& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0;
 }
#endif
 return (double)b/a.value;
}
// Float operations reversed (leans toward float precision)
double operator+ ( const Zdouble& a, float b ) { return a.value+(double)b; }
double operator- ( const Zdouble& a, float b ) { return a.value-(double)b; }
double operator* ( const Zdouble& a, float b ) { return a.value*(double)b; }
double operator/ ( const Zdouble& a, float b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0f ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0;
 }
#endif

 return a.value/(double)b;
}

/// Zdouble and double

// Casted double operations
double operator+ ( double b, const Zdouble& a ) { return a.value+b; }
double operator- ( double b, const Zdouble& a ) { return b-a.value; }
double operator* ( double b, const Zdouble& a ) { return a.value*b; }
double operator/ ( double b, const Zdouble& a ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( a.value == 0.0) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0;
 }
#endif
 return b/a.value;
}
// Casted double operations reversed
double operator+ ( const Zdouble& a, double b ) { return a.value+b; }
double operator- ( const Zdouble& a, double b ) { return a.value-b; }
double operator* ( const Zdouble& a, double b ) { return a.value*b; }
double operator/ ( const Zdouble& a, double b ) {
#if defined(DIV_BY_ZERO_PROTECTION)
 if ( b == 0.0 ) {
#if defined(DIV_BY_ZERO_REPORTING)
  qDebug() << ("Zdouble: divide by zero in / operation!");
#endif
  return 0.0;
 }
#endif
 return a.value/b;
}

// Boolean operations
bool operator>= ( const Zdouble& a, const Zdouble& b ) { return ( a.value >= b.value );    }
bool operator>= ( const Zdouble& a, int b )            { return ( a.value >= (double) b ); }
bool operator>= ( const Zdouble& a, float b )          { return ( a.value >= (double) b ); }
bool operator>= ( const Zdouble& a, double b )         { return ( a.value >= b );          }
bool operator>= ( int a, const Zdouble& b )            { return ( (double) a >= b.value ); }
bool operator>= ( float a, const Zdouble& b )          { return ( (double) a >= b.value ); }
bool operator>= ( double a, const Zdouble& b )         { return ( a >= b.value );          }
bool operator== ( const Zdouble& a, const Zdouble& b ) { return ( a.value == b.value );    }
bool operator== ( const Zdouble& a, int b )            { return ( a.value == (double) b ); }
bool operator== ( const Zdouble& a, float b )          { return ( a.value == (double) b ); }
bool operator== ( const Zdouble& a, double b )         { return ( a.value == b );          }
bool operator== ( int a, const Zdouble& b )            { return ( (double) a == b.value ); }
bool operator== ( float a, const Zdouble& b )          { return ( (double) a == b.value ); }
bool operator== ( double a, const Zdouble& b )         { return ( a == b.value );          }
bool operator!= ( const Zdouble& a, const Zdouble& b ) { return ( a.value != b.value );    }
bool operator!= ( const Zdouble& a, int b )            { return ( a.value != (double) b ); }
bool operator!= ( const Zdouble& a, float b )          { return ( a.value != (double) b ); }
bool operator!= ( const Zdouble& a, double b )         { return ( a.value != b );          }
bool operator!= ( int a, const Zdouble& b )            { return ( (double) a != b.value ); }
bool operator!= ( float a, const Zdouble& b )          { return ( (double) a != b.value ); }
bool operator!= ( double a, const Zdouble& b )         { return ( a != b.value );          }
bool operator<= ( const Zdouble& a, const Zdouble& b ) { return ( a.value <= b.value );    }
bool operator<= ( const Zdouble& a, int b )            { return ( a.value <= (double) b ); }
bool operator<= ( const Zdouble& a, float b )          { return ( a.value <= (double) b ); }
bool operator<= ( const Zdouble& a, double b )         { return ( a.value <= b );          }
bool operator<= ( int a, const Zdouble& b )            { return ( (double) a <= b.value ); }
bool operator<= ( float a, const Zdouble& b )          { return ( (double) a <= b.value ); }
bool operator<= ( double a, const Zdouble& b )         { return ( a <= b.value );          }
bool operator> ( const Zdouble& a, const Zdouble& b )  { return ( a.value > b.value );    }
bool operator> ( const Zdouble& a, int b )             { return ( a.value > (double) b ); }
bool operator> ( const Zdouble& a, float b )           { return ( a.value > (double) b ); }
bool operator> ( const Zdouble& a, double b )          { return ( a.value > b );          }
bool operator> ( int a, const Zdouble& b )             { return ( (double) a > b.value ); }
bool operator> ( float a, const Zdouble& b )           { return ( (double) a > b.value ); }
bool operator> ( double a, const Zdouble& b )          { return ( a > b.value );          }
bool operator< ( const Zdouble& a, const Zdouble& b )  { return ( a.value < b.value );    }
bool operator< ( const Zdouble& a, int b )             { return ( a.value < (double) b ); }
bool operator< ( const Zdouble& a, float b )           { return ( a.value < (double) b ); }
bool operator< ( const Zdouble& a, double b )          { return ( a.value < b );          }
bool operator< ( int a, const Zdouble& b )             { return ( (double) a < b.value ); }
bool operator< ( float a, const Zdouble& b )           { return ( (double) a < b.value ); }
bool operator< ( double a, const Zdouble& b )          { return ( a < b.value );          }

/// Zdouble ////////////////////////////////////////////////////////////////////////////////////////// end



/// Zstring (UTF-8) ////////////////////////////////////////////////////////////////////////////////////////// end

const char string_error='\0';

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>


// Work Strings
char buf[STRING_SIZE];
char buf2[STRING_SIZE];
char buf3[STRING_SIZE];

void InitZeroTypesLibrary() {
 for ( int i=0; i<STRING_SIZE; i++ ) buf[i]=buf2[i]=buf3[i]='\0';
 init_seeder();
}


void rtrim(string& s, const string& delimiters ) {
   s.erase( s.find_last_not_of( delimiters ) + 1 );
}

void ltrim(string& s,  const string& delimiters ) {
   s.erase( 0, s.find_first_not_of( delimiters ) );
}

void trim(string& s, const string& delimiters ) {
    s.erase( s.find_last_not_of( delimiters ) + 1 ).erase( 0, s.erase( s.find_last_not_of( delimiters ) + 1 ).find_first_not_of( delimiters ) );
}


// Gather until next substring match or end of string (returns the point right after the substring)
const char *gather_to( const char *argument, const char *substr, string *buf ) {
 *buf=string("");
 int substrlen=(int)strlen(substr);
 const char *p=argument;
 bool found=false;
 while ( *p != '\0' && !found ) {
  if ( *p==*substr ) {
   const char *oldp=p;
   const char *q=substr;
   bool match=true;
   int i=0;
   while ( match && i<substrlen ) {
    if ( *p!=*q ) match=false;
    p++;
    q++;
    i++;
   }
   if ( match ) {
    found=true;
    return p;
   }
   else {
    p=oldp;
    *buf+=(*p);
    p++;
   }
  } else {
   *buf+=(*p);
   p++;
  }
 }
 return p;
}


// Gather until next substring match or end of string (returns the point right after the substring)
const char *gather_to( const char *argument, char endchar, string *buf ) {
 const char *p=argument;
 while ( *p != '\0' && *p != endchar ) {
  *buf += (*p);
  p++;
 }
 return p;
}

void replaceOnce(string& in, string const &search, string const &substitute) {
 int found=0;
 string::size_type pos=0;
 while((pos=in.find(search, pos))!=string::npos&&found<1)
 {
  in.erase(pos, search.length());
  in.insert(pos, substitute);
  pos+=substitute.length();
  found++;
 }
}

void replaceAll(string& in, string const &search, string const &substitute) {
 string::size_type pos=0;
 while((pos=in.find(search, pos))!=string::npos)
 {
  in.erase(pos, search.length());
  in.insert(pos, substitute);
  pos+=substitute.length();
 }
}

string replace_all(const string& in, const string& search, const string& substitute) {
 string::size_type pos=0;
 string out=in;
 while((pos=out.find(search, pos))!=string::npos)
 {
  out.erase(pos, search.length());
  out.insert(pos, substitute);
  pos+=substitute.length();
 }
 return out;
}


bool endsWith(string const &fullString, string const &ending) {
 string a=fullString;
 trim(a);
 if (a.length() >= ending.length()) {
  return (0 == a.compare(a.length() - ending.length(), ending.length(), ending));
 } else {
  return false;
 }
}

bool endsWith( const char *searching, const char *find, bool removePadding ) {
 if ( searching == nullptr ) {
  qDebug() << ( "endsWith: nullptr searching." );
  return false;
 }
 if ( find == nullptr ) {
  qDebug() << ( "endsWith: nullptr find." );
  return false;
 }
 int L1=(int)strlen(searching);
 if ( L1 == 0 ) return false;
 int L2=(int)strlen(find);
 if ( L1<L2 ) return false;
 if ( L2 == 0 ) {
  qDebug() << ("endsWith() warns find string was empty, returning false\n");
  return false;
 }
 string unpadded;
 if ( !removePadding ) unpadded=string(searching);
 else {
  unpadded=string(searching);
  trim(unpadded);
  L1=(int)unpadded.length();
  if ( L1<L2 ) return false;
 }
 const char *tosearch=unpadded.c_str();
 int x=L1-1;
 int y=L2-1;
 while ( y>=0 ) {
  if ( LOWER(tosearch[x]) != LOWER(find[y]) ) {
   return false;
  }
  x--;
  y--;
 }
 return true;
}

/*
 * Counts the number of "words" (strings of non-spaces separated by spaces)
 * in a string.     Not the best way (should use one_arg)?
 */
int words(const char *argument )
{
 int total;
 char *s = (char *) argument;
 total = 0;
 while ( *s != '\0' )
  if ( *s != ' ' ) {
   total++;
   while ( *s != ' ' && *s != '\0' ) s++;
  } else s++;
 return total;
}

/*
 * Compare strings, case insensitive.
 * Return true if different
 *   (compatibility with historical functions).
 */
bool str_cmp( const char *astr, const char *bstr )
{
 if ( astr == nullptr ) {
  qDebug() << ( "Str_cmp: nullptr astr." );
  return true;
 }
 if ( *astr == '\0' ) return true;
 if ( bstr == nullptr ) {
  qDebug() << ( "Str_cmp: nullptr bstr." );
  return true;
 }
 if ( *bstr == '\0' ) return true;
 for ( ; *astr || *bstr; astr++, bstr++ ) if ( LOWER(*astr) != LOWER(*bstr) ) return true;
 return false;
}

bool str_cmp( string astr, string bstr ) {
 return str_cmp( astr.c_str(), bstr.c_str() );
}

inline bool is_digit( char c ) {
 return (c =='0' || c == '1' || c == '2' || c == '3' || c == '4' || c =='5' || c =='6' || c=='7' || c == '8' || c == '9' );
}

bool char_in(char c, const char *list ) {
 int o,O;
 O=(int)strlen(list);
 for ( o=0; o<O; o++ ) if ( list[o] == c ) return true;
 return false;
}

/*
 * Compare strings, case sensitive.
 * Return true if different
 *   (compatibility with historical functions).
 */
bool str_cmp_case( const char *astr, const char *bstr )
{
 if ( astr == nullptr ) {
  qDebug() << ( "Str_cmp: nullptr astr." );
  return true;
 }
 if ( bstr == nullptr ) {
  qDebug() << ( "Str_cmp: nullptr bstr." );
  return true;
 }
 for ( ; *astr || *bstr; astr++, bstr++ ) if ( (*astr) != (*bstr) ) return true;
 return false;
}

string lower( string a ) {
 Zstring lowered;
 const char *p=a.c_str();
 while ( *p != '\0' ) { char b=LOWER(*p); lowered+=b; p++; }
 return lowered.value;
}


/*
 * Return true if an argument is completely numeric.
 */
bool is_integer( const char *arg ) {
 const char *o=arg;
 bool foundspace=false;
 if ( *arg == '\0' ) return false;
 if ( *arg == '-' ) arg++;
 for ( ; *arg != '\0'; arg++ ) {
  if ( !is_digit(*arg) ) {
   if ( _FILLER(*arg) ) foundspace=true;
   else return false;
  }
 }
 if ( foundspace ) {
  if ( words(o) == 1 ) return true;
  return false;
 }
 return true;
}

/*
 * Return true if an argument is completely numeric.
 */
bool is_decimal( const char *arg ) {
 const char *o=arg;
 int periods=0;
 bool foundspace=false;
 if ( *arg == '\0' ) return false;
 while ( _FILLER(*arg) ) arg++;
 if ( *arg == '-' ) arg++;
 for ( ; *arg != '\0'; arg++ ) {
  if ( !is_digit(*arg) ) {
   if ( *arg == '.' ) {
    if ( periods >=1 ) return false;
    periods++;
    arg++;
   } else
   if ( _FILLER(*arg) ) foundspace=true;
   else return false;
  }
 }
 if ( foundspace ) {
  if ( words(o) == 1 ) return true;
  return false;
 }
 return true;
}

/*
 * Same as above but uses atoi error handling, decimal only (base-10, no floats).
 * Does not return the value if valid (tiny inefficiency).
 * Source: http://www.gidforums.com/t-17778.html
 */
bool is_int( string k ) {
 const char *in=k.c_str();
 char * last = 0;
 strtol(in, &last, 10);
 if ( *last == '\0' ) // was valid or empty
  if ( k.length() > 0 ) return false;
 return true;
}

/*
 * Same as above but uses atoi error handling.  Only base 10 checked.
 * Does not return the value if valid (tiny inefficiency).
 * Source: http://www.gidforums.com/t-17778.html
 */
bool is_hex( string k ) {
 const char *in=k.c_str();
 char *last = nullptr;
 strtol(in, &last, 16);
 if ( last && *last == '\0' ) // was valid or empty
  if ( k.length() > 0 ) return false;
 return true;
}

/*
 * Same as above but uses atoi error handling, decimal only (base-10, no floats).
 * Does not return the value if valid (tiny inefficiency).
 * Source: http://www.gidforums.com/t-17778.html
 */
bool is_float( string k ) {
 char * last = 0;
 strtol(k.c_str(), &last, 10);
 if ( *last == '\0' ) // was valid or empty returns false positive (indicating no error, but does not specify why)
  if ( k.length() > 0 ) return false;
 return true;
}

int from_hex( string hex ) {
 int result;
#if IS_WINDOWS
 sscanf_s(hex.c_str(), "%x", &result);
#else
 sscanf(hex.c_str(), "%x", &result);
#endif
 return result;
}

string to_hex(int i) {
 char buf[80];
 FORMAT(buf, 80, "%x", (int)i);
 string out = string(buf);
 if (out.length() == 1) out = string("0") + out; // A==0A
 return out;
}

string to_hexidecimal( int i ) {
 char buf[80];
 FMT(buf,80,"%x", (int) i);
 string out=string(buf);
 if ( out.length() == 1 ) out=string("0")+out; // A==0A
 return out;
}

/* Pick off one argument from a string and return the rest.
 * Understands quotes and {}=[], treats interim commas and equal signs as space.
 * Uses the stack so not recommended for large strings (use string_argument);
 */
const char *one_argument( const char *args, char *arg_first )
{
 const char *argument=args;
 char cEnd = ' ';
 if ( argument == nullptr ) return &string_error;
 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
 while ( _FILLER(*argument) || *argument == '#' ) {
  if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 if ( _SEP(*argument) ) {
  cEnd = *argument;
  argument++;
 }
 if ( _NESTERS(*argument) ) { // Handle nested {} or []
  argument++;
  int nests=1;
  while ( *argument != '\0' && _NESTERE(*argument) && nests > 0 ) {
   if ( _NESTERE(*argument) ) {
    nests--;
    argument++;
    if ( nests == 0 ) break;
   } else if ( *argument == '{' || *argument == '[' ) nests++;
   *arg_first=*argument;
   argument++;
   arg_first++;
  }
 } else { // Quotes are the delimiters
  while ( *argument != '\0' ) {
   if ( *argument == '\n' ) {
    argument++;
    if ( cEnd == ' ' ) break;
   }
   if ( *argument == '\r' ) {
    argument++;
    if ( cEnd == ' ' ) break;
   }
   if ( *argument == ',' && cEnd == ' ' ) break; // end on a comma unless quotes are cEnd
   if ( *argument == '=' && cEnd == ' ' ) break; // end on equal sign unless quotes are cEnd
   if ( *argument == cEnd ) {
    argument++;
    break;
   }
   *arg_first = LOWER(*argument);
   arg_first++;
   argument++;
  }
 }
 *arg_first = '\0';
 // Advance past spaces and interim commas, equal signs, newlines, skip #comments
 while ( _FILLER(*argument) || *argument == '#' ) {
  if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 return argument;
}

/* Pick off one argument from a string and return the rest.
 * Understands quotes and {}=[], treats interim commas and equal signs as space.
 * Uses the stack so not recommended for large strings (use string_argument);
 */
const char *one_argument_case( const char *args, char *arg_first )
{
 const char *argument=args;
 char cEnd = ' ';
 if ( argument == nullptr ) return &string_error;
 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
 while ( _FILLER(*argument) || *argument == '#' ) {
  if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 if ( _SEP(*argument) ) {
  cEnd = *argument;
  argument++;
 }
 if ( _NESTERS(*argument) ) { // Handle nested {} or []
  argument++;
  int nests=1;
  while ( *argument != '\0' && _NESTERE(*argument) && nests > 0 ) {
   if ( _NESTERE(*argument) ) {
    nests--;
    argument++;
    if ( nests == 0 ) break;
   } else if ( *argument == '{' || *argument == '[' ) nests++;
   *arg_first=*argument;
   argument++;
   arg_first++;
  }
 } else { // Quotes are the delimiters
  while ( *argument != '\0' ) {
   if ( *argument == '\n' ) {
    argument++;
    if ( cEnd == ' ' ) break;
   }
   if ( *argument == '\r' ) {
    argument++;
    if ( cEnd == ' ' ) break;
   }
   if ( *argument == ',' && cEnd == ' ' ) break; // end on a comma unless quotes are cEnd
   if ( *argument == '=' && cEnd == ' ' ) break; // end on equal sign unless quotes are cEnd
   if ( *argument == cEnd ) {
    argument++;
    break;
   }
   *arg_first = (*argument);
   arg_first++;
   argument++;
  }
 }
 *arg_first = '\0';
 // Advance past spaces and interim commas, equal signs, newlines, skip #comments
 while ( _FILLER(*argument) || *argument == '#' ) {
  if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 return argument;
}


/* Pick off one argument from a string and return the rest.
 * Understands quotes.
 */
const char *one_argcase(const char *argument, char *arg_first) {
 char cEnd;
 if (argument == nullptr) return &string_error;
 while ((*argument == ' ') || *argument == '\n' || *argument == '\r')	argument++;
 cEnd = ' ';
 if (*argument == '\'' || *argument == '"' || *argument == '\'') cEnd = *argument++;
 else if (*argument == '{') { cEnd = '}'; argument++; }
 while (*argument != '\0') {
  if (*argument == '\n') { argument++; if (cEnd == ' ') break; }
  if (*argument == '\r') { argument++; if (cEnd == ' ') break; }
  if (*argument == cEnd) { argument++; break; }
  *arg_first = (*argument);
  arg_first++;
  argument++;
 }
 *arg_first = '\0';
 while ((*argument == ' ') || *argument == '\n' || *argument == '\r') argument++;
 return argument;
}

/* Pick off one argument from a string and return the rest.
 * Uses std::string thus dynamic and doesn't use the stack.
 * Understands quotes and {}=[](), treats interim commas and equal signs as space.
 */
const char *string_argument( const char *argument, string *arg_first, bool slash_comments, bool pound_comments )
{
 char cEnd = ' ';
// char buf[2];
 (*arg_first)=string("");
 if ( argument == nullptr ) return &string_error; // undef behavior? maybe "" is constant
 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
 while ( _FILLER(*argument) /*|| (*argument == '#' && pound_comments)*/ ) {
  if ( slash_comments && *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  //else if ( pound_comments && *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 // Handle nested {} [] (), or quotes "" '' ``
 if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
  int nests=1;
  char cStart=*argument;
  argument++;
  switch ( cStart ) {
   case '{': cEnd = '}'; break;
   case '[': cEnd = ']'; break;
   case '(': cEnd = ')'; break;
  case '\'': cEnd = '\''; break;
   case '"': cEnd = '"'; break;
   case '`': cEnd = '`'; break;
  }
  while ( *argument != '\0' && nests > 0 ) {
   if ( *argument == cEnd ) {
    nests--;
    if ( nests == 0 ) break;
   } else if ( *argument == cStart ) nests++;
   (*arg_first)+=(*argument);
   argument++;
  }
  argument++;
 } /*else if ( _EXPRESSIVE(*argument) ) {
  (*arg_first)+=*argument;
 }*/ else { // No delimiters, lower case, stop when you hit = , [ { ( + / - * % ! <space>
  while ( *argument != '\0' ) {
   if ( char_in( *argument, "\n\r[{(,= " ) ) break;
   (*arg_first)+=LOWER(*argument);//string(buf);
   argument++;
  }
 }
 // Advance past spaces and interim commas, equal signs, newlines, skip #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  /*if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else*/ argument++;
 }
 return argument;
}


/* Pick off one argument from a string and return the rest without lowering case.
 * Uses std::string thus dynamic and doesn't use the stack.
 * Understands quotes and {}=[](), treats interim commas and equal signs as space.
 */
const char *string_argument_case( const char *argument, std::string *arg_first )
{
 char cEnd = ' ';
// char buf[2];
 (*arg_first)=string("");
 if ( argument == nullptr ) return &string_error; // undef behavior? maybe "" is constant
 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  //else if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 // Handle nested {} [] (), or quotes "" '' ``
 if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
  int nests=1;
  char cStart=*argument;
  argument++;
  switch ( cStart ) {
   case '{': cEnd = '}'; break;
   case '[': cEnd = ']'; break;
   case '(': cEnd = ')'; break;
  case '\'': cEnd = '\''; break;
   case '"': cEnd = '"'; break;
   case '`': cEnd = '`'; break;
  }
  while ( *argument != '\0' && nests > 0 ) {
   if ( *argument == cEnd ) {
    nests--;
    if ( nests == 0 ) break;
   } else if ( *argument == cStart ) nests++;
   (*arg_first)+=(*argument);
   argument++;
  }
  argument++;
 } else { // No delimiters, lower case, stop when you hit = , [ { (
  while ( *argument != '\0' ) {
   if ( char_in( *argument, "\n\r[{(,= " ) ) break;
   (*arg_first)+=(*argument);//string(buf);
   argument++;
  }
 }
 // Advance past spaces and interim commas, equal signs, newlines, skip #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  /*if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else*/ argument++;
 }
 return argument;
}



/* Pick off one argument from a string and return the rest without lowering case.
 * Uses std::string thus dynamic and doesn't use the stack.
 * Understands quotes and {}=[](), treats interim commas and equal signs as space.
 */
const char *string_argument_case( const char *argument, std::string *arg_first, bool *hit_semicolon_at_end )
{
 char cEnd = ' ';
// char buf[2];
 (*arg_first)=string("");
 if ( argument == nullptr ) return &string_error; // undef behavior? maybe "" is constant
 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  //else if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 // Handle nested {} [] (), or quotes "" '' ``
 if ( _NESTERS(*argument) || _SEP(*argument) ) { // Delimiters
  int nests=1;
  char cStart=*argument;
  argument++;
  switch ( cStart ) {
   case '{': cEnd = '}'; break;
   case '[': cEnd = ']'; break;
   case '(': cEnd = ')'; break;
  case '\'': cEnd = '\''; break;
   case '"': cEnd = '"'; break;
   case '`': cEnd = '`'; break;
  }
  while ( *argument != '\0' && nests > 0 ) {
   if ( *argument == cEnd ) {
    nests--;
    if ( nests == 0 ) break;
   } else if ( *argument == cStart ) nests++;
   (*arg_first)+=(*argument);
   argument++;
  }
  argument++;
 } else { // No delimiters, lower case, stop when you hit = , [ { ( or the special endcase
  while ( *argument != '\0' ) {
   if ( *argument == ';' ) { if (hit_semicolon_at_end) *hit_semicolon_at_end=true; argument++; break; }
   else if ( char_in( *argument, "\n\r[{(,= " ) ) break;
   (*arg_first)+=(*argument);//string(buf);
   argument++;
  }
 }
 // Advance past spaces and interim commas, equal signs, newlines, skip #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  /*if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else*/ argument++;
 }
 return argument;
}



/* Pick off one argument from a string and return the rest.
 * Uses std::string thus dynamic and doesn't use the stack.
 * Understands quotes and {}=[](), treats interim commas and equal signs as space.
 */
const char *string_argument_end( const char *argument, string *arg_first, char *sep )
{
 char cEnd = ' ';
// char buf[2];
 (*arg_first)=string("");
 if ( argument == nullptr ) return &string_error; // undef behavior? maybe "" is constant
 // Advance past spaces and interim commas, equal signs, newlines, skip //comments and #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  if ( *argument == '/' && *(argument+1) == '/' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  //else if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else argument++;
 }
 // Handle nested {} [] (), or quotes "" '' ``
 if ( char_in(*argument, "{([`'\"") ) { // Delimiters
  int nests=1;
  char cStart=*argument;
  switch ( cStart ) {
   case '{': cEnd = '}'; break;
   case '[': cEnd = ']'; break;
   case '(': cEnd = ')'; break;
  case '\'': cEnd = '\''; break;
   case '"': cEnd = '"'; break;
   case '`': cEnd = '`'; break;
  }
  argument++;
  while ( *argument != '\0' && nests > 0 ) {
   if ( *argument == cEnd ) {
    nests--;
    if ( nests == 0 ) break;
   } else if ( *argument == cStart ) nests++;
   /*buf[0]=*argument;
   buf[1]='\0';*/
   (*arg_first)+=(*argument);//string(buf);
   argument++;
  }
  argument++;
 } else { // No delimiters, lower case, stop when you hit = , [ { (
  while ( *argument != '\0' ) {
   if ( char_in( *argument, "\n\r[{(,= " ) ) { *sep=*argument; } break;
   /*buf[0]=(*argument);
   buf[1]='\0';*/
   (*arg_first)+=LOWER(*argument);//string(buf);
   argument++;
  }
 }
 // Advance past spaces and interim commas, equal signs, newlines, skip #comments
 while ( _FILLER(*argument) /*|| *argument == '#'*/ ) {
  /*if ( *argument == '#' ) while ( *argument != '\n' && *argument != '\r' && *argument != '\0' ) argument++;
  else*/ argument++;
 }
 return argument;
}


/*
 * Compare strings, case insensitive, for prefix matching.
 * Return true if hay not a prefix of haystack
 *   (compatibility with historical functions).
 */
bool str_prefix( const char *astr, const char *bstr )
{
 if ( astr == nullptr || *astr == '\0' ) {
  qDebug() << ( "Str_prefix: nullptr astr." );
  return true;
 }
 if ( bstr == nullptr || *bstr == '\0'  ) {
  qDebug() << ( "Str_prefix: nullptr bstr." );
  return true;
 }
 while ( *astr != '\0' && *bstr != '\0' ) {
  if ( LOWER(*astr) != LOWER(*bstr) ) return true;
  astr++;
  bstr++;
 }
 if ( *astr == '\0' ) return false;
 return true;
}

/*
 * Compare strings, case sensitive, for prefix matching.
 * Return true if astr not a prefix of bstr
 *   (compatibility with historical functions).
 */
bool str_prefix_case( const char *astr, const char *bstr )
{
 if ( astr == nullptr || *astr == '\0' ) {
  qDebug() << ( "Str_prefix: nullptr astr." );
  return true;
 }
 if ( bstr == nullptr || *bstr == '\0'  ) {
  qDebug() << ( "Str_prefix: nullptr bstr." );
  return true;
 }
 while ( *astr != '\0' && *bstr != '\0' ) {
  if ( (*astr) != (*bstr) ) return true;
  astr++;
  bstr++;
 }
 return false;
}

string strtolower( const char *input ) {
 return lower(string(input));
}

/*
 * Compare strings, case insensitive, for match anywhere.
 * Returns true if shorter string not part of longer string.
 *   (compatibility with historical functions).
 */
bool str_infix( const char *astr, const char *bstr ) {
 if ( astr == nullptr || *astr == '\0' ) {
  qDebug() << "Str_infix: nullptr astr (compared against '" << bstr << "'\n";
  return true;
 }
 if ( bstr == nullptr || *bstr == '\0' ) {
  qDebug() << "Str_infix: nullptr bstr (compared against '" << astr << "'\n";
  return true;
 }
 const char *key,*haystack,*q;
 // Figure out which string is shorter, and use that as a key (q)
 if ( strlen(astr) > strlen(bstr) ) {
  haystack= (char *) astr;
  key=q= (char *) bstr;
 } else {
  haystack= (char *) bstr;
  key=q= (char *) astr;
 }
 // Make the keyword lowercase;
 string _key=lower(string(key));
 q=_key.c_str();
 char start=(*q);
 bool found=false;
 while ( *haystack !='\0' && !found ) {
  if ( LOWER(*haystack) != start ) { haystack++; continue; }
  if ( strlen(haystack) < _key.length() ) break;
  q=_key.c_str();
  while ( *q != '\0' && *haystack!='\0' && *q==LOWER(*haystack) ) { q++; haystack++; }
  if ( *q == '\0' ) { found=true; break; }
 }
 return !found;
}


/*
 * Compare strings, case insensitive, for match anywhere.
 * Returns true if shorter string not part of longer string.
 *   (compatibility with historical functions).
 */
bool str_infix_case( const char *astr, const char *bstr ) {
    if ( astr == nullptr || *astr == '\0' ) {
     qDebug() << "Str_infix: nullptr astr (compared against '" << bstr << "'\n";
     return true;
    }
    if ( bstr == nullptr || *bstr == '\0' ) {
     qDebug() << "Str_infix: nullptr bstr (compared against '" << astr << "'\n";
     return true;
    }
 const char *key,*p,*q;
 // Figure out which string is shorter, and use that as a key (q)
 if ( strlen(astr) > strlen(bstr) ) {
  p= (char *) astr;
  key=q= (char *) bstr;
 }
 else {
  p= (char *) bstr;
  key=q= (char *) astr;
 }
 // Make the keyword lowercase;
 char start=(*q);
 int keyLength=(int)strlen(key);
 bool found=false;
 while ( *p!='\0' && !found ) {
  if ( LOWER(*p) != start ) { p++; continue; }
  if ( (int)strlen(p) < keyLength ) break;
  q=key;
  while ( *q != '\0' && *p!='\0' && *q==LOWER(*p) ) { q++; p++; }
  if ( *q == '\0' ) { found=true; break; }
 }
 return !found;
}

bool string_infix( string astr, string bstr ) {
 string a=string(astr); std::transform(a.begin(), a.end(), a.begin(),(int(*)(int)) std::tolower);
 string b=string(bstr); std::transform(b.begin(), b.end(), b.begin(),(int(*)(int)) std::tolower);
 if ( b.find(a) != string::npos ) return false;
 return true;
}

/*
 * Compare strings, case insensitive, for suffix matching.
 * Return true if astr not a suffix of bstr
 *   (compatibility with historical functions).
 */
bool str_suffix( const char *astr, const char *bstr )
{
 size_t sstr1;
 size_t sstr2;
 if ( !astr || !bstr ) return true;
 sstr1 = strlen(astr);
 sstr2 = strlen(bstr);
 if ( sstr1 <= sstr2 && !str_cmp( astr, bstr + sstr2 - sstr1 ) ) return false;
 else return true;
}

// Determines how many "words" in a string
int Zstring::words() {
 Strings s;
 s.SplitPush(value.c_str());
 return s.count.value;
}

// Removes all newlines, limits all spaces to 1
string Zstring::Words() {
 Zstring out;
 out=value;
 out("\n"," ");
 out("\t"," ");
 while ( out.Contains("  ") ) out("  "," ");
 const char *p=value.c_str();
 while ( *p != '\0' ) {
  p++;
  string word;
  p=string_argument_case(p,&word);
  if ( word.length() > 0 ) {
   if ( out.length > 0 ) {
    result+=" ";
   }
   result+=word;
  }
 }
 return out.value;
}

// Limits to a length or less without breaking words ex: LimitTo(dog cat fish ~ 6) = dog
string Zstring::LimitTo( int len ) {
 Strings words;
 words.SplitPush(Words().c_str(),' ');
 Zstring out;
 EACH(words.first,String,s) {
  if ( (int)out.length + (int)s->s.length() > len ) break;
  out+=s->s;
 }
 return out.value;
}

string Zstring::WordWrap( int linelen ) {
 Strings words;
 words.SplitPush(Words().c_str(),' ');
 Zstring out;
 Zint thislinelen;
 EACH(words.first,String,s) {
  int wordlen=(int)s->s.length();
  if ( (int)thislinelen + 1 + wordlen > linelen ) {
   out+="\n";
   out+=s->s+string(" ");
   thislinelen=(int)s->s.length();
  } else {
   out+=s->s+string(" ");
   thislinelen+=wordlen+1;
  }
 }
 return out.value;
}

bool Zstring:: is_inside( const char * cloud ) {
 Zstring c(cloud);
 Strings it;
 it.SplitPush(cloud);
 Strings us;
 us.SplitPush(this->c_str());
 return it.includes(&us);
}


void Zstring::Load(const char * s) {
 (*this) = file_as_string(s);
}

bool operator== ( const Zstring& a, const Zstring& b ) {
 bool result= !str_cmp(a.value.c_str(),b.value.c_str());
 if ( !result ) {
  if ( is_decimal(a.value.c_str()) && is_decimal(b.value.c_str()) ) {
   double A=atof(a.value.c_str());
   double B=atof(b.value.c_str());
   return ( A == B );
  }
 }
 return result;
}

bool operator== ( const Zstring& a, const char * b ) {
 return !str_cmp(a.value.c_str(),b);
}

bool operator== ( const char * b, const Zstring& a ) {
 return !str_cmp(a.value.c_str(),b);
}

string operator+ ( const Zstring& a, const Zstring& b ) {
 return a.value+b.value;
}

string operator+ ( const Zstring& a, const string& b ) {
 return a.value+b;
}

string operator+ ( const string& a, const Zstring& b ) {
 return a+b.value;
}

string operator+ ( const Zstring& a, const int& b ) {
 return a.value+FORMAT(tbuf,128,"%d",(int)b);
}

string operator+ ( const Zstring& a, const unsigned int& b ) {
 return a.value+FORMAT(tbuf,128,"%d",(int)b);
}

string operator+ ( const Zstring& a, const float& b ) {
 return a.value+FORMAT(tbuf,128,"%f",(float)b);
}

string operator+ ( const Zstring& a, const double& b ) {
 return a.value+FORMAT(tbuf,128,"%f",(double)b);
}

string operator+ ( const int& a, const Zstring& b ) {
 return b.value+FORMAT(tbuf,128,"%d",(int)a);
}

string operator+ ( const unsigned int& a, const Zstring& b ) {
 return b.value+FORMAT(tbuf,128,"%d",(int)a);
}

string operator+ ( const float& a, const Zstring& b ) {
 return b.value+FORMAT(tbuf,128,"%f",(float)a);
}

string operator+ ( const double& a, const Zstring& b ) {
 return b.value+FORMAT(tbuf,128,"%f",(double)a);
}

string operator+ ( string a, Zint& b )    { return a+b.toString(); }
string operator+ ( string a, Zuint& b )   { return a+b.toString(); }
string operator+ ( string a, Zfloat& b )  { return a+b.toString(); }
string operator+ ( string a, Zdouble& b ) { return a+b.toString(); }
/* Creates C2593
string operator+ ( Zint& a, string b )    { return a.toString()+b; }
string operator+ ( Zuint& a, string b )   { return a.toString()+b; }
string operator+ ( Zfloat& a, string b )  { return a.toString()+b; }
string operator+ ( Zdouble& a, string b ) { return a.toString()+b; }
*/


int operator+ ( Zint& a, Zint& b ) { return a.value+b.value; }
float operator+ ( Zfloat& a, Zfloat& b ) { return a.value+b.value; }
double operator+ ( Zdouble& a, Zdouble& b ) { return a.value+b.value; }

string operator+ ( const Zstring& a, char c ) {
 return a.value+c;
}

string operator+ ( char c, const Zstring& a ) {
 return a.value+c;
}

string operator- ( const Zstring& a, const Zstring& b ) {
 string result=a.value;
 replaceOnce(result,b.value,string(""));
 return result;
}

string operator- ( const Zstring& a, const string& b ) {
 string result=a.value;
 replaceOnce(result,b,string(""));
 return result;
}

string operator- ( const string& b, const Zstring& a ) {
 string result=b;
 replaceOnce(result,a.value,string(""));
 return result;
}

string operator- ( const Zstring& a, const char *b ) {
 string result=a.value;
 replaceOnce(result,string(b),string(""));
 return result;
}

/*
string operator- ( const char *b, const Zstring& a ) {
 string result=string(b);
 replaceOnce(result,a.value,string(""));
 return result;
}*/

string operator/ ( const Zstring& a, const Zstring& b ) {
 string result=a.value;
 replaceAll(result,b.value,string(""));
 return result;
}

string operator/ ( const Zstring& a, const string& b ) {
 string result=a.value;
 replaceAll(result,b,string(""));
 return result;
}

string operator/ ( const string& b, const Zstring& a ) {
 string result=b;
 replaceAll(result,a.value,string(""));
 return result;
}

string operator/ ( const Zstring& a, const char *b ) {
 string result=a.value;
 replaceAll(result,string(b),string(""));
 return result;
}

string operator/ ( const char *b, const Zstring& a ) {
 string result=string(b);
 replaceAll(result,a.value,string(""));
 return result;
}

string operator* ( const Zstring& a, unsigned int i ) {
 string temp=string("");
 for ( unsigned int j=0; j<i; j++ ) {
  temp+=a.value;
 }
 return temp;
}

int operator* ( const Zstring& a, string b ) {
 if (a.value.length() == 0) return 0;
 int count = 0;
 for (
  size_t offset = a.value.find(b);
  offset != std::string::npos;
     offset = a.value.find(b, offset + b.length())
   ) ++count;
 return count;
}

int operator* ( string a, const Zstring& b ) {
 if (a.length() == 0) return 0;
 int count = 0;
 for (
  size_t offset = a.find(b.value);
  offset != std::string::npos;
     offset = a.find(b.value, offset + b.value.length())
   ) ++count;
 return count;
}

int operator* ( const Zstring& a, const char *B ) {
 string b=string(B);
 if (a.value.length() == 0) return 0;
 int count = 0;
 for (
  size_t offset = a.value.find(b);
  offset != std::string::npos;
     offset = a.value.find(b, offset + b.length())
   ) ++count;
 return count;
}

int operator* ( const Zstring& a, const Zstring& b ) {
 if (a.value.length() == 0) return 0;
 int count = 0;
 for (
  size_t offset = a.value.find(b.value);
  offset != std::string::npos;
     offset = a.value.find(b.value, offset + b.value.length())
   ) ++count;
 return count;
}

/// Zstring ////////////////////////////////////////////////////////////////////////////////////////// end



// This is an up-to-date unit test for the ZIndexed template.
// Do not define NEVER, simply remove the #if-def block.
void ZIndexed_Rigorous_Test() {
#if defined(NEVER)
 qDebug() << ("ZIndexed_Rigorous_Test: Phase I: allocating, initializing and destroying.");
 for ( unsigned int i=0; i<100; i++ ) {
  ZIndexed<unsigned int> b;
  b.Size(1024*1024);
  for ( unsigned int j=0; j<1024*1024; j++ ) {
   b(j)=j;
  }
 }
 qDebug() << ("ZIndexed_Rigorous_Test: Phase II: resizing.");
 ZIndexed<unsigned int> b;
 for ( unsigned int i=0; i<100; i++ ) {
  b.Size(i*i*i);
  for ( unsigned int j=0; j<i*i*i; j++ ) {
   b(j)=j;
  }
 }
 qDebug() << ("ZIndexed_Rigorous_Test: Phase III: complex Zero-memory tasks.");
 for ( unsigned int i=0; i<100; i++ ) {
  ZIndexed<Zpointer<unsigned int>> c;
   c.Size(i*i*i);
  for ( unsigned int j=0; j<i*i*i; j++ ) {
   c(j)=&i;
  }
 }
 qDebug() << ("ZIndexed_Rigorous_Test: Phase IV: complex disposable-memory tasks.");
 for ( unsigned int i=0; i<100; i++ ) {
  if ( i % 2 == 0 ) qDebug() << (".");
  ZIndexed<Zdisposable<ZIndexed<unsigned int>>> c;
   c.Size(i);
  for ( unsigned int j=0; j<i; j++ ) {
   c(j).Recycle();
   c(j)->Size(j);
//   for ( unsigned int k=0; k<j; j++ ) {
   // (*c(j)->Element(k))=k;
//   }
  }
 }
 qDebug() << ("ZIndexed_Rigorous_Test: Phase V: complex disposable-memory tasks with linear increase.");
 ZIndexed<Zdisposable<Zstring>> c;
 for ( unsigned int i=0; i<100; i++ ) {
  c.Increase();
  if ( i % 2 == 0 ) qDebug() << (".");
  for ( unsigned int j=0; j<i+1; j++ ) {
   c(j).Recycle();
//   for ( unsigned int k=0; k<j; j++ ) {
   // (*c(j)->Element(k))=k;
//   }
  }
 }
 qDebug() << ("\n");
 qDebug() << ("Indexed_Rigorous_Test: Complete.");
#endif
}

//////////////////////////////////////////// ListItem and LinkedList

Zint anyReseed;
ListItem *LinkedList::Any( int seed ) {
 if ( count == 0 ) return nullptr;
 anyReseed++;
 return Element(pseudorandom(count*2,anyReseed)%count);
}

void LinkedList::sendUp(ListItem *L, bool wrap)
{
 if ( wrap ) {
  if ( L->prev ) {
   ListItem *before=L->prev;
   Remove(L);
   InsertBefore(L,before);
  } else {
   Remove(L);
   Append(L);
  }
 } else if ( L->prev ) {
  ListItem *before=L->prev;
  Remove(L);
  InsertBefore(L,before);
 }
}

void LinkedList::sendDown(ListItem *L, bool wrap)
{
 if ( wrap ) {
  if ( L->next ) {
   ListItem *after=L->next;
   Remove(L);
   InsertAfter(L,after);
  } else {
   Remove(L);
   Prepend(L);
  }
 } else if ( L->next ) {
  ListItem *after=L->next;
  Remove(L);
  InsertAfter(L,after);
 }
}

// Adds to end of list
void LinkedList::Append(ListItem *L) {
 _Append(L);
}

// Adds to end of list
void LinkedList::_Append(ListItem *L) {
 count++;
 if ( last ) {
  last->next=L;
  L->prev=last;
  L->next=nullptr;
  last=L;
  return;
 }
 L->next=L->prev=nullptr;
 first=last=L;
}

// Adds to beginning of list
void LinkedList::Prepend(ListItem *L) {
 count++;
 if ( first ) {
  first->prev=L;
  L->next=first;
  L->prev=nullptr;
  first=L;
  return;
 }
 L->next=L->prev=nullptr;
 first=last=L;
}

// Finds element at index i, if none returns nullptr
// 0=first
 ListItem *LinkedList::Element(int i) {
 ListItem *l;
 if ( count.value == 0 || i >= count.value ) return nullptr;
 int c=0;
 for ( l=first; l; l=l->next ) {
  if ( c==i ) return l;
  c++;
 }
 if ( first ) return first;
 if ( last ) return last;
 qDebug() << ("LinkedList::Element(index) returned nullptr because the list was empty.");
 return nullptr;
}

ListItem *LinkedList::Element(int i, bool wrap) {
 ListItem *l;
 if ( count.value == 0 ) return nullptr;
 i%=count.value;
 int c=0;
 for ( l=first; l; l=l->next ) {
  if ( c==i ) return l;
  c++;
 }
 if ( first ) return first;
 if ( last ) return last;
 qDebug() << ("LinkedList::Element(index) returned nullptr because the list was empty.");
 return nullptr;
}

int LinkedList::Element( ListItem *q ) {
 int i=0;
 FOREACH(ListItem,p) if ( p == q ) return i; else i++;
 qDebug() << ("LinkedList::Element(item) returned -1 because the item was not found.");
 return -1;
}

// Inserts element L before p ListItem in List
void LinkedList::InsertBefore(ListItem *insert, ListItem *before) {
 if ( !before ) { Prepend(insert); return; }
 insert->prev=before->prev;
 if ( insert->prev ) insert->prev->next=insert;
 insert->next=before;
 before->prev=insert;
 if ( before == first ) first=insert;
 count++;
}

// Inserts element L after p ListItem in List
void LinkedList::InsertAfter(ListItem *insert, ListItem *after) {
 if ( !after ) { Prepend(insert); return; }
 insert->next=after->next;
 if ( after->next ) after->next->prev=insert;
 after->next=insert;
 insert->prev=after;
 if ( after == last ) last=insert;
 count++;
}

// Inserts element at index i (before), if index i exists, otherwise returns false
void LinkedList::InsertAt(ListItem *insert, int i) {
 ListItem *p=Element(i);
 InsertBefore(insert,p);
}

// Removes element L from list
void LinkedList::_Remove(ListItem *L) {
#if defined(DEBUG)
 if ( !this->ListIteminList(L) ) {
  qDebug() << ("Warning: attempted to remove something not in this list.\n");
  return;
 }
#endif
 if ( first==L ) {
  if ( first==last ) {
   first=last=nullptr;
   L->next=L->prev=nullptr;
   count=0;
   return;
  }
  first=first->next;
  if ( first ) first->prev=nullptr;
  L->next=L->prev=nullptr;
  count--;
  return;
 }
 if ( last==L ) {
  last=last->prev;
  if ( last ) last->next=nullptr;
  L->next=L->prev=nullptr;
  count--;
  return;
 }
 ListItem *p=L->prev,*n=L->next;
 if ( p ) p->next=n;
 if ( n ) n->prev=p;
 L->next=L->prev=nullptr;
 count--;
 return;
}

// Removes all elements from the list
void LinkedList::RemoveAll(void) {
 first=last=nullptr;
 count=0;
}

// Deletes (frees) element L from list
void LinkedList::Delete(ListItem *L) {
 Remove(L);
 delete L;
}

// Deletes (frees) element L from list, clears incoming
void LinkedList::Delete(ListItem **L) {
 Remove(*L);
 delete (*L);
 *L=nullptr;
}


void LinkedList::RandomizeOrder() {
 LinkedList newList;
 EACHN(first,ListItem,i,{
  Remove(i);
  if ( uniform() >= 0.5 ) {
   newList.Prepend(i);
  } else {
   newList.Append(i);
  }
 });
 this->first=newList.first; newList.first=nullptr;
 this->last=newList.last; newList.last=nullptr;
 count=newList.count; newList.count=0;
 return;
}

//////////////////////////////////////////// Strings and precursor required math

string UnStringSpecialCodes( string k ) {
 return replace_all(replace_all(k,string("#*$#-1-#$*#"),string("{")),string("#*$#-2-#$*#"),string("}"));
}

string StringSpecialCodes( string k ) {
 return replace_all(replace_all(k,string("{"),string("#*$#-1-#$*#")),string("}"),string("#*$#-2-#$*#"));
}


///// Random Numbers


// Constants needed for random generation

const long m = 2147483647L;
const long a = 48271L;
const long q = 44488L;
const long r = 3399L;

// A variable used to initialize the generator (should never be 0).
long r_seed = 12345678L;


double uniform ()
{
  long t, lo, hi;
  double u;

  hi = r_seed / q;
  lo = r_seed - q * hi;
  t = a * lo - r * hi;
  if (t > 0)
    r_seed = t;
  else
    r_seed = t + m;
  u = (double) r_seed / (double) m ;

  return u;
}

double uniform ( bool reseed )
{
  long t, lo, hi;
  double u;

  hi = r_seed / q;
  lo = r_seed - q * hi;
  if ( reseed ) {
   t = a * lo - r * hi;
   if (t > 0)
     r_seed = t;
   else
     r_seed = t + m;
  }
  u = (double) r_seed / (double) m ;

  return u;
}

// Works better with small numbers 0-255, used in Randoms.h,
// Adheres to RAND_MAX (0x7fff) but is intended to be distinct and non-OS specific
int pseudorandom( unsigned int s, unsigned int x ) {
 s++;
 x++;
 long S=s;
 long X=x;
 long result=((56789*(X+S*X+S))/2)%PSEUDORAND_MAX;
 return abs((int)result);
}

/*
#include <chrono>
long getMillis(void) {
 return std::chrono::system_clock::now().time_since_epoch().count();
}
 */

#include <sys/time.h>
long getMillis(void) {
 struct timeval tp;
 gettimeofday(&tp, NULL);
 long long ms = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000L;
 return (long) ms;
}

#ifndef LONG_MIN
#define LONG_MIN ((long long) -9223372036854775808)
#endif

#ifndef ULONG_MAX
#define ULONG_MAX 0xFFFFFFFFUL
#endif

// Reseeding
void init_seeder() {
 r_seed = (long) ( getMillis() );
 r_seed = (long) (uniform()*ULONG_MAX);
 if ( r_seed == 0 ) r_seed++;
}

void reseed() {
 r_seed = (long) ( getMillis() );
 r_seed = (long) (uniform()*ULONG_MAX);
 if ( r_seed == 0 ) r_seed++;
}

double random(double x) {
    return x*uniform();
}

// Properly rounds ints
int iround ( float f ) {
 return (int)(f+0.5f);
}

// Properly rounds ints
int iround ( double d ) {
 return (int)(d+0.5);
}

// Do a floating point lerp from "start" to "finish"
int ilerp( int start, int end, float percent ) {
 int d;
 if ( start > end ) {
  d=start-end;
  return start-iround( (float) d * percent );
 } else {
  d=end-start;
  return start+iround( (float) d * percent );
 }
}

// Do a floating point lerp from "start" to "finish"
int ilerpw( int start, int end, float percent ) {
 float d=((float)ADIFF(start,end));
 if ( start > end ) d=-d;
 return start+iround( d * percent );
}


// Do a floating point lerp from "start" to "finish"
int ilerp( int start, int end, double percent ) {
 int d;
 if ( start > end ) {
  d=start-end;
  return start-iround( (double) d * percent );
 } else {
  d=end-start;
  return start+iround( (double) d * percent );
 }
}

// Do a floating point lerp from "start" to "finish"
int ilerpw( int start, int end, double percent ) {
 double d=((double)ADIFF(start,end));
 if ( start > end ) d=-d;
 return start+iround( d * percent );
}

double double_range( double L, double H ) {
 double u=uniform();
 double t=(H-L);
 u*= t;
 return (u) + L;
}

float float_range( float L, float H ) {
 double u=uniform();
 double t= (double) (H-L);
 u*= t;
 return ((float) u) + L;
}

// Randomize an integer in range L-H
int number_range( int L, int H ) {
   double u=uniform();
   int t=H-L;
   u*=(double) t;
   u+=(double) L;
   return iround((float) (u));
}

int upto( int M ) {
 if ( M==0 ) return 0;
 return number_range(0,M*2)%M;
//  return (int) (uniform()/*0.999999999999999*/*(double) max);
}


// Generating gaussian random number with mean 0 and standard deviation 1.
float Gauss()
{
    double u1 = uniform();
    double u2 = uniform();
    if (u1 < 1e-6f) u1 = 1e-6f;
    return sqrtf(-2 * logf((float) u1)) * cosf((float)(2*PI*u2));
}


char randomChar( const char *list ) {
 int c=(int)upto((int)strlen(list));
 return list[c];
}

// Used when writing to a file.
/* in-den-tion (noun) \in-'den(t)-shun\ archaic : indentation;
 a: the action of indenting : the condition of being indented
 b: the blank space produced by indenting
 */
string indention=string("");

void incdent() {
 indention+=string(" ");
}

void decdent() {
 size_t spaces=indention.length();
 spaces--;
 nodent();
 for ( int i=0; i<(int)spaces; i++ ) incdent();
}

void nodent() {
 indention=string("");
}

// Low-brow alphanumeric hash.
string Hash( int len ) {
 if ( len<1 ) len=1;
 char *buf;
 buf = new char[len+1];
 for ( int i=0; i<len; i++ ) buf[i]=randomChar("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
 buf[len]='\0';
 string s=string(buf);
 delete[] buf;
 return s;
}


bool HashCompare5( string *a, string *b ) {
 const char *A=a->c_str();
 const char *B=b->c_str();
 return ( A[0]==B[0] && A[1]==B[1] && A[2]==B[2] && A[3]==B[3] && A[4]==B[4] );
}

// Pseudo-
string RomanNumerals( int v ) {
 switch ( v ) {
 case 1: return string("I");
 case 2: return string("II");
 case 3: return string("III");
 case 4: return string("IV");
 case 5: return string("V");
 case 6: return string("VI");
 case 7: return string("VII");
 case 8: return string("VIII");
 case 9: return string("IX");
 case 10: return string("X");
 case 11: return string("X1");
 case 12: return string("X2");
 case 13: return string("X3");
 case 14: return string("X4");
 case 15: return string("X5");
 case 16: return string("X6");
 case 17: return string("X7");
 case 18: return string("X8");
 case 19: return string("X9");
 case 20: return string("2X");
 case 21: return string("2Xi");
 case 22: return string("2Xii");
 case 23: return string("2Xiii");
 case 24: return string("2Xiv");
 case 25: return string("2Xv");
 case 26: return string("2Xvi");
 case 27: return string("2Xvii");
 case 28: return string("2Xviii");
 case 29: return string("2X9");
 case 30: return string("3X");
 default:
  {
   char buf[128];
   if ( v%10 == 0 ) FORMAT(buf,128,"%d", (int) v);
   else {
    string numbers=RomanNumerals(v%10);
    numbers=lower(numbers);
    FORMAT(buf,128,"%dX%s", (int)(v/10), numbers.c_str() );
   }
   return string(buf);
  }
 }
}



string slash_to_backslash( const char * s ) {
 Zstring in(s);
 in("/","\\");
 return in.c_str();
}

string backslash_to_slash( const char * s ) {
 Zstring in(s);
 in("\\","/");
 return in.c_str();
}

string trailing_slash( const char *s ) {
 Zstring in(s);
 in.Trim();
 if ( in.last() != '/' ) in+=string("/");
 return in.value;
}

string basename( const char *path, char sep ) {
 Zstring a=path;
 Zstring s(sep);
 a(s.c_str(),"/");
 return _basename(a.c_str());
}

string _basename( const char *path ) {
 std::string filename=path;
 // Remove directory if present.
 // Do this before extension removal incase directory has a period character.
 const size_t last_slash_idx = filename.find_last_of("\\/");
 if (std::string::npos != last_slash_idx) filename.erase(0, last_slash_idx + 1);
 // Remove extension if present.
 const size_t period_idx = filename.rfind('.');
 if (std::string::npos != period_idx) filename.erase(period_idx);
 return filename;
}

string trailing_backslash( const char *s ) {
 Zstring in(s);
 in.Trim();
 if ( in.last() != '\\' ) in+=string("\\");
 return in.value;
}

int StringToHash( const char *s, int size ) {
 int index=0;
 int len=(int)strlen(s);
 if ( len <= 0 ) return 0;
 int a=len/4;        if ( a > len-1 ) a=len; int c_a=(int)s[a];
 int b=len/2;        if ( b > len-1 ) b=len; int c_b=(int)s[b];
 int c=len/2+len/4;  if ( c > len-1 ) c=len; int c_c=(int)s[c];
 int d=len/3;        if ( d > len-1 ) d=len; int c_d=(int)s[d];
 int e=len/3*2;      if ( e > len-1 ) e=len; int c_e=(int)s[e];
 int f=len-1;        if ( f > len-1 ) f=len; int c_f=(int)s[f];
 return (int)(((c_a+c_b+c_c+c_d+c_e+c_f)%size));
}



/*
   base64.cpp and base64.h

   Copyright (C) 2004-2008 Ren? Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   Ren? Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

// B64K functions: Swaps out the two B64 characters that don't work in URLs.
string b64k_encode(const char *in) {
 Zstring piped(in);
 piped = base64_encode(piped.value);
 piped("/", "_");
 piped("+", "-");
 piped("#", "!");
 return piped.value;
}

string b64k_decode(const char *in) {
 Zstring piped(in);
 piped("-", "+");
 piped("_", "/");
 piped("!", "#");
 return base64_decode(piped.value);
}


static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
 return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_encode(string const& s) {
 unsigned char const *bytes_to_encode = reinterpret_cast<const unsigned char*>(s.c_str());
 std::string ret;
 size_t in_len = s.length();
 int i = 0;
 int j = 0;
 unsigned char char_array_3[3];
 unsigned char char_array_4[4];

 while (in_len--) {
  char_array_3[i++] = *(bytes_to_encode++);
  if (i == 3) {
   char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
   char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
   char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
   char_array_4[3] = char_array_3[2] & 0x3f;

   for (i = 0; (i < 4); i++)
    ret += base64_chars[char_array_4[i]];
   i = 0;
  }
 }

 if (i)
 {
  for (j = i; j < 3; j++)
   char_array_3[j] = '\0';

  char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
  char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
  char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
  char_array_4[3] = char_array_3[2] & 0x3f;

  for (j = 0; (j < i + 1); j++)
   ret += base64_chars[char_array_4[j]];

  while ((i++ < 3))
   ret += '=';

 }

 return ret;

}

string base64_decode(string const& encoded_string) {
 size_t in_len = encoded_string.size();
 int i = 0;
 int j = 0;
 int in_ = 0;
 unsigned char char_array_4[4], char_array_3[3];
 char_array_4[0] = '\0';
 char_array_4[1] = '\0';
 char_array_4[2] = '\0';
 char_array_4[3] = '\0';
 char_array_3[0] = '\0';
 char_array_3[1] = '\0';
 char_array_3[2] = '\0';
 Zstring ret;

 while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
  char_array_4[i++] = encoded_string[in_]; in_++;
  if (i == 4) {
   for (i = 0; i < 4; i++)
    char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

   char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
   char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
   char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

   for (i = 0; (i < 3); i++)
    ret += char_array_3[i];
   i = 0;
  }
 }

 if (i) {
  for (j = i; j < 4; j++)
   char_array_4[j] = 0;

  for (j = 0; j < 4; j++)
   char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

  char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
  char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
  char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

  for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
 }

 return ret;
}

/* -- END base64 */

/////////////////////////////////////////////////////////////// Strings

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>



// String

const char *String::c_str() {
 return this->s.c_str();
}

void Strings::Load(const char *filepath) {
 SplitPush(file_as_string(filepath).c_str());
}

void Strings::ls_( const char *targetPath, bool listFiles, bool prependPath, bool filterOSFiles ) {
 Strings *folder=ls(targetPath,listFiles,prependPath,filterOSFiles);
 if ( folder ) {
  Concat(folder);
  delete folder;
 }
}

bool Strings::inList( string s ) {
 FOREACH(String,sL) if ( s == sL->s ) return true;
 return false;
}

String *Strings::matchPrefix( const char *s ) {
 FOREACH(String,sL) if ( sL->s.length() > 0 && strlen(s) > 0 && !str_prefix(sL->c_str(),s) ) return sL;
 return nullptr;
}

void Strings::matchesPrefix( const char *s, Strings *out ) {
 FOREACH(String,sL) {
  if ( sL->s.length() > 0 && strlen(s) > 0 && !str_prefix(sL->c_str(),s) ) {
   out->Push(sL->s.c_str());
  }
 }
}

String *Strings::match( const char *s ) {
 FOREACH(String,sL) if ( !str_cmp(sL->c_str(),s) ) return sL;
 return nullptr;
}

String *Strings::find( string s ) {
 FOREACH(String,sL) if ( s == sL->s ) return sL;
 return nullptr;
}

String *Strings::find( const char *s ) {
 string f=string(s);
 FOREACH(String,sL) if ( f == sL->s ) return sL;
 return nullptr;
}

String *Strings::findCaseless( const char *s ) {
 string f=string(s);
 FOREACH(String,sL) if ( !str_cmp(s, sL->s.c_str() ) ) return sL;
 return nullptr;
}

String *Strings::findCaseless( string s ) {
 string f=string(s);
 FOREACH(String,sL) if ( !str_cmp((char *) s.c_str(), (char *) sL->s.c_str() ) ) return sL;
 return nullptr;
}

 String *Strings::findSubstring( const char *s ) {
  FOREACH(String,sL) if ( !str_prefix(sL->s.c_str(),s) ) return sL;
  return nullptr;
 }
 String *Strings::contains(const char *s) {
  FOREACH(String, sL) if (!str_infix(sL->s.c_str(), s)) return sL;
  return nullptr;
 }
 String *Strings::findNextSubstring( String *start, const char *s ) {
  String *sL=start;
  while ( sL && string_infix(s,sL->s) ) sL=(String *) sL->next;
  return sL;
 }

 string Strings::concatToNextSubstring( String *start, const char *end ) {
  String *e = this->findNextSubstring(start,end);
  string x=string("");
  String *sL=start;
  while ( sL && sL != e ) { x+=sL->s+string("\n"); sL=(String *) sL->next; }
  return x;
 }

// Returns -1 if not in list
int Strings::IndexOf( String *s ) {
 int i=0;
 FOREACH(String,sL) {
  if ( s == sL ) return i;
  else i++;
 }
 return -1;
}

// Returns duplicated concatenations of Strings
string Strings::Concatenate( char seperator ) {
 string e = string("");
 FOREACH(String,sL) {
  e=e+sL->s;
  e.append( 1, seperator );
 }
 return e;
}

// Returns duplicated concatenations of Strings
string Strings::Concatenate( having Seamless ) {
 string e = string("");
 FOREACH(String,sL) {
  e=e+sL->s;
 }
 return e;
}

void Strings::appendFromString( const char *s, char c ) {
 static char temp[STRING_SIZE];
 const char *p= s;
 int i=0;
 while ( *p != '\0' ) {
  if ( *p==c ) {
   temp[i]='\0';
   String *t; NEW(t,String(temp));
   if (!t) {
    qDebug() << ("appendFromString: error on allocation, Could not allocate new string.");
    return;
   }
   Append(t);
   i=0;
  } else
  temp[i++] =*p;
  p++;
 }
}

void Strings::appendFromString( string s, char c ) {
 appendFromString( (char *) s.c_str(), c );
}

void Strings::show()
{
 FOREACH(String,s) qDebug() << s->s.c_str() << "\n";
}

void Strings::show( const char *sep, const char *end )
{
 FOREACH(String,s) qDebug() << s->s.c_str() << (s->next ? sep : "") << "\n";
 qDebug() << end << "\n";
}

// Splits using string_argument
void Strings::SplitPush( const char *s ) {
 const char *p=s;
 while ( *p != '\0' ) {
  string t;
  p=string_argument(p,&t);
  if ( t.length() > 0 ) Push(t);
 }
}


// Splits by char_in(), like char_isof
void Strings::SplitPush( const char *s, const char *delimiterList ) {
 const char *p=s;
 Zstring t;
 while ( *p != '\0' ) {
  if ( char_in(*p,delimiterList) && t.length > 0 ) { Add(t.c_str()); t=""; }
  else t+=(*p);
  p++;
 }
 if ( t.length > 0 ) Add(t.c_str());
}

void Strings::SplitPush( string s, char seperator ) {
 string t;
 static char buf[2];
 buf[0]=seperator;
 buf[1]='\0';
 const char *p=s.c_str();
 while ( *(p=gather_to(p,buf,&t)) != '\0' ) Push(t);
 if ( t.length() > 0 ) Push(t);
}



void Strings::SplitPush( const char *s, char separator ) {
 Zstring t;
 const char *p=s;
 while ( *p != '\0' ) {
  if ( *p == separator ) {
   Push(t.value);
   t="";
   p++;
   continue;
  }
  t+=*p;
  p++;
 }
 if ( t.length > 0 ) Push(t.value);
}


// Splits using string_argument
void Strings::ScriptPush( const char *s ) { SplitPush(s); }

void Strings::Push( string s ) {
 String *t; NEW(t,String(s));
 if (!t) {
  qDebug() << ("Push: error on allocation, Could not allocate new string.");
  return;
 }
 Append(t);
}

void Strings::Push( const char *s ) {
 String *t; NEW(t,String(s));
 if (!t) {
  qDebug() << ("Push: error on allocation, Could not allocate new string.");
  return;
 }
 Append(t);
}

String *Strings::PushAndGet( const char *s ) {
 String *x; NEW(x,String(string(s)));
 if (!x) {
  qDebug() << ("PushAndGet: error on allocation, Could not allocate new string.");
  return nullptr;
 }
 Append(x);
 return x;
}

void Strings::DuplicateAndPush( const char *s ) { // No longer different
 String *t; NEW(t,String(s));
 if (!t) {
  qDebug() << ("DuplicateAndPush: error on allocation, Could not allocate new string.");
  return;
 }
 Append( t );
}

void StringsList::Parent( StringsList *newParent ) {
 if ( parent && parent->children ) parent->children->Drop(this);
 parent=newParent;
 if ( parent ) parent->children->Add(this);
}

void StringsList::AddChild( StringsList *s ) {
 if ( !children ) children.Instantiate();
 s->Parent(this);
}

bool StringsList::ParentOf( StringsList *s ) {
 if ( !children ) return false;
 if ( s->parent == this ) return true;
 EACH(children->first,StringsListHandle,slh) {
  if ( slh->p->ParentOf(s) ) return true;
 }
 return false;
}

bool StringsList::DirectParentOf( StringsList *s ) {
 if ( !children ) return false;
 if ( s->parent == this ) return true;
 return false;
}

bool StringsList::DirectChildOf( StringsList *s ) {
 if ( !parent ) return false;
 if ( parent == s ) return true;
 return false;
}

void StringsList::Lineage() {
 lineage.Recycle();
 if ( !graph ) return;
 if ( parent ) {
  parent->Lineage();
  EACH(parent->lineage->first,StringsListHandle,slh) {
   lineage->Add(slh->p);
  }
 }
 lineage->Add(this);
}

bool StringsList::ChildOf( StringsList *s ) {
 if ( !parent ) return false;
 if ( parent == s ) return true;
 if ( parent->ChildOf(s) ) return true;
 return false;
}

void StringsList::Dependants( StringsListHandles *out ) {
 if ( children ) EACH(children->first,StringsListHandle,slh) {
  slh->p->Dependants(out);
  out->Add(slh->p);
 }
}

void StringsList::Children( StringsListHandles *out ) {
 Dependants(out);
}

void StringsList::Detach() {
 if ( !graph ) return; // If we're not in a graph already, this would be null, indicating it is already detached.
 graph->Remove(this);
 this->graph=nullptr;
 if ( parent && parent->children ) parent->children->Drop(this);
 if ( children && children->count > 0 ) {
  StringsListHandles removing;
  Dependants(&removing);
  EACHREV(removing.last,StringsListHandle,slh) {
   slh->p->parent=nullptr;
   slh->p->Detach();
   delete slh->p; // We delete the children after they have been detached.
  }
 }
 // We don't delete ourself here.
}

void StringsList::Dispose() {
 Detach();
 delete this;
}



// List directory contents

namespace fs = std::experimental::filesystem;
void inPath( Strings &out, const char *path ) {
// std::string filepath = std::string(path);
// for (const auto & entry : fs::directory_iterator(filepath)) out.Add(entry.path().c_str());
}

void inRecursePath( Strings &out, const char *path ) {
// std::string filepath = std::string(path);
// for (const auto & entry : fs::recursive_directory_iterator(filepath)) out.Add(entry.path().c_str());
}

#include <sys/stat.h>

bool isFolder( const char *path ) {
    struct stat s;
    if ( stat(path,&s) == 0 && s.st_mode && S_IFDIR ) return true;
    return false;
}

bool isFile( const char *path ) {
    struct stat s;
    if ( stat(path,&s) == 0 && s.st_mode && S_IFREG ) return true;
    return false;
}

Strings *ls( const char *targetPath, bool listFiles, bool prependPath, bool filterOSFiles ) {
 Strings path;
 inPath(path,targetPath);
 Strings *list; NEW(list,Strings);
 Zstring fullPath,current;
 EACH(path.first,String,it) {
  current = it->s;
  if (filterOSFiles) {
   if (current == "Thumbs.db") continue;
   if (current == "desktop.ini") continue;
   if (current == "system.ini") continue;
   if (current == ".") continue;
   if (current == "..") continue;
  }
  fullPath=string(targetPath)+it->s;
  bool isDir = isFolder(fullPath.c_str());
  if (prependPath) {
   if (isDir && !listFiles) list->Add((string(targetPath) + current.value).c_str());
   else if (isFile(fullPath.c_str())) list->Add((string(targetPath) + current.value).c_str());
  } else {
   if (isDir && !listFiles) list->Add(current.c_str());
   else if (isFile) list->Add(current.c_str());
  }
 }
 return list;
}

bool file_exists( const char *filepath ) {
  struct stat buffer;
  return (stat (filepath, &buffer) == 0) && isFile(filepath); 
}

bool folder_exists( const char *filepath ) {
  struct stat buffer;
  return (stat (filepath, &buffer) == 0) && isFolder(filepath); 
}

#include <fstream>
#include <streambuf>

int filesize( const char *filepath ) {
  if ( file_exists(filepath) ) {
    std::ifstream in(filepath, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
  }
}

bool string_as_file( const char *sout, const char *filepath ) {
  fstream file;
  file.open(filepath, ios::out );
  if ( !file.is_open() ) return false;
  file << sout << endl;
  file.close();
  return true;
}

std::string file_as_string( const char *filepath ) {
 if ( !file_exists(filepath) ) return std::string("");
 std::ifstream t(filepath);
 std::string str;
 t.seekg(0, std::ios::end);   
 str.reserve(t.tellg());
 t.seekg(0, std::ios::beg);
 str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
 return str;
}

json file_as_json( const char *filepath ) {
 json js = json::parse(file_as_string(filepath));
 return js;
}

bool json_as_file( json &j, const char *filepath ) {
 return string_as_file(j.dump().c_str(),filepath);
}
/*
bool json_true_false( const QJsonValue &v ) {
 if ( v.isBool() ) return v.toBool();
 else if ( v.isDouble() ) return v.toDouble() > 0.0 ? true : false;
 else if ( v.isString() ) {
  Zstring s=v.toString().toStdString();
  if ( s.length == 0 ) return false;
  if ( LOWER(s.At(0)) == 'y' ) return true;
  if ( LOWER(s.At(0)) == 'n' ) return false;
  if ( LOWER(s.At(0)) == 't' ) return true;
  if ( LOWER(s.At(0)) == 'f' ) return false;
  if ( s.At(0) == '1' ) return true;
 }
 return false;
}

bool json_true_false( const json &o, const char *keyname, bool defaultValue ) {
 if ( !o.contains(keyname) ) return defaultValue;
 QJsonValue v=o[keyname];
 return json_true_false(v);
}

std::string json_get_string( const json &o, const char *keyname ) {
 if ( o.contains(keyname) ) return o[keyname].toString().toStdString();
 return string("");
}

bool json_cmp_string( const json &o, const char *keyname, const char *other_value ) {
 return !str_cmp(json_get_string(o,keyname).c_str(),other_value);
}

bool json_filled_string( const json &o, const char *keyname ) {
 if ( o.contains(keyname)
   && o[keyname].isString()
   && o[keyname].toString().length() > 0 ) return true;
 return false;
}

bool json_only_defined( const json &o, int count, ... ) {
 if ( count != o.size() ) return false;
 va_list args;
 va_start( args, count );
 for ( int i=0; i < count; i++ ) {
  if ( !o.contains(va_arg(args,const char *)) ) return false;
 }
 va_end(args);
 return true;
}

bool json_req_defined( const json &o, int count, ... ) {
 if ( count < o.size() ) return false;
 va_list args;
 va_start( args, count );
 for ( int i=0; i < count; i++ ) {
  if ( !o.contains(va_arg(args,const char *)) ) return false;
 }
 va_end(args);
 return true;
}
*/
std::string json_to_string( const json &o ) {
 return o.dump();
}



// Integer SQRT
#define MAX_SRT 10000
double SRT[MAX_SRT];
int SRT_initialized=0;
void init_isqrt( ) {
 int i;
 for ( i =0; i< MAX_SRT; i++ ) SRT[i]=sqrt((double)i);
 SRT_initialized=1;
}
double isqrt ( int i ) {
 i=abs(i);
 if ( i > MAX_SRT-1 ) return (float) sqrt((float) i);
 return (float) SRT[i];
}
