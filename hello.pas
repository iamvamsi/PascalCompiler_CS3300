{MORE KEYWORDS - type, record, file, in, with, repeat, until, case}
{ this is a comment }
program example(output, input);

var x,y,k : integer;
   l,m	  : real;
    w,z	  : boolean;
   a,b	  : char;

function gcd(a,b : integer) : integer;
begin		      
   if b <= 0 then gcd := a
   else gcd := gcd(b, a mod b)
end; { gcd }	      

begin
   {read(x,y);}
   x := 5; y := 10;
   l := gcd(x,y);
   l := 4;
   m := l + x
   {writeln (gcd (x,y))}
   {k := m;}
   {b := 2}
end.
