program test(input,output);
var num,m,v : integer;
   f,g	    : real;
   a,b,c    : char;
   k,l,t    : boolean;
   i	    : array [2 .. 4] of integer;
   j	    : array [2 .. 4] of integer;
begin
   i[2] := 3;
   i[3] := 4;
   i[4] := 5;
   num := 5;
   m := not num; {bitwise NOT}
   {a := 'r';}
   k := false;
   l := true;
   t := k<l
   {writeln (t);
   writeln (i[2]>i[3])}
   {
   f := 0;
   if f = 0 then
      num := 3.4e-2
   else
      num := (3<=4) + (4-2);
   num := num or f
   }
end.

