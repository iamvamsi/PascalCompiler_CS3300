program example (input);
var a,b,c : integer;

procedure func(a : integer);
begin
   a := 23
end; { func }

function myfunc(a : integer ) : integer;
begin
   myfunc := 5 + a
end;

begin
   b := 3; a := myfunc(b);

   while a < b do
      c := 10;
   
   if a < b then 
	c := 2
   else 
	c := 5
end.
