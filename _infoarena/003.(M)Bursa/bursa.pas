var n,i,antant,ant,min,x:longint;
    s,sin,act:int64;

begin
  assign(input,'bursa.in'); reset(input);
  assign(output,'bursa.out'); rewrite(output);

  readln(n,sin);
  s := sin;

  case n of
    1: write('0');
    2: begin
         read(antant,ant);
         if antant > ant then
           write('0')
         else
         begin
           act := s div antant;
           s := s - act*antant;
           s := s + act*ant;
           write(s-sin);
         end;
       end;
     else
     begin
       read(antant,ant);  act := 0;
       if antant < ant then min := antant else min := ant;

       for i := 3 to n do
       begin
         read(x);
         if (antant <= ant) and (ant > x) then
         begin
           act := s div min;
           s := s - act*min;
           s := s + act*ant;
           act := 0;
           min := x;
         end;
         if min > x then min := x;
         antant := ant;
         ant := x;
       end;

       if antant <= ant then
       begin
         act := s div min;
         s := s - act*min;
         s := s + act*ant;
         act := 0;
       end;

       write(s-sin);

     end;
  end;


  close(input);
  close(output);
end.
