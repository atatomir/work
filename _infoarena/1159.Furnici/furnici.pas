type furnica=record
       pos:longint;
       dir:char;
     end;
var l,n,i:longint;
    a:array[1..100001]of furnica;
    bufin,bufout:array[1..65000]of byte;
    primas,primad:longint;
    x:char;

begin
  assign(input,'furnici.in'); reset(input);
  assign(output,'furnici.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(l,n);
  for i := 1 to n do
    readln(a[i].pos,x,a[i].dir);

  primas := 999999999; primad := 0;

  for i := 1 to n do
  begin
    if (a[i].dir = 'D') and (a[i].pos < primas) then
    begin
      primas := a[i].pos;
    end;
    if (a[i].dir = 'S') and (a[i].pos > primad) then
    begin
      primad := a[i].pos;
    end;

  end;



  primas := l - primas ;

  if primas = 999999999 then
    write(primad)
  else
    if primad = 0 then
      write(primas)
    else
      if primas > primad then write(primas) else write(primad);


  close(input);
  close(output);
end.
