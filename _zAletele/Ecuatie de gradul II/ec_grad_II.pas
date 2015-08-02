var a,b,c,delta:real;
    x1,x2:real;


begin
  writeln('Program de rezolvare a ecuatiei de gradul II !');
  writeln('Creat de Alex Tatomir!');
  repeat
    writeln('--------------------------------------------------');
    writeln('Ecuatie de forma ax^2^+bx+c = 0');
    write('a = '); read(a);
    write('b = '); read(b);
    write('c = '); read(c);
    writeln();
    if a = 0 then
    begin
      writeln('Atentie! a <> 0 ! Reincearca!');
    end
    else
    begin
      delta := b*b - 4*a*c;
      if delta < 0 then
      begin
        writeln('*Ecuatia nu are solutii!');
      end
      else
      begin
        if delta = 0 then
        begin
          x1 := (-b) / (2*a);
          writeln('X = ',x1:10:2);
        end
        else
        begin
          delta := sqrt(delta);
          x1 := (-b + delta)/(2*a);
          x2 := (-b - delta)/(2*a);
          writeln('X1 = ',x1:10:2,' |  X2 = ',x2:10:2);
        end;
      end;
    end;
  until false;

end.
