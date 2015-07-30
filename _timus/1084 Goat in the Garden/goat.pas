uses math;
var l,r,rez,u,x,a:real;

begin
  read(l,r);

  if r <= l/2 then rez := PI *r*r
  else
  if r >= l/sqrt(2) then rez := l*l
  else
  begin
    u := arccos(l/(2*r));
    u := u*180/PI;
    u := 90 - 2*u;

    x := sqrt(r*r - l*l/4);
    a := l*l/4 - x*l/2 - (PI*r*r*u/360);
    rez := l*l - 4*a;

  end;


  write(rez:0:3);
end.