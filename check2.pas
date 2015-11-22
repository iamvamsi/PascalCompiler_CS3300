program example;

procedure global;
   procedure temp11;
      procedure temp111;
      begin
	 writeln ("In temp3")
      end;
   begin
      { temp3 IS VISIBLE ONLY HERE }
      temp111;
      writeln ("In first temp")
   end; { temp }

   procedure temp12;
      procedure temp121;
	 procedure temp1211;
	 begin
	    temp111
	 end;
      begin
	 writeln ("In second temp")
      end; { temp1 }
   
      procedure temp122;
      begin
	 temp121;
	 writeln ("In third temp")
      end; { temp }
   begin
      temp122; { INVOKES THE INNERMOST temp FUNCTION}
      temp121; { INVOKES THE temp1 THAT WAS DECLARED IN THIS SCOPE; NOT A RECURSIVE CALL }
      writeln ("In temp1")
   end; { temp1 }

begin
   temp11;
   temp12
end; { global }

begin
   global
end.