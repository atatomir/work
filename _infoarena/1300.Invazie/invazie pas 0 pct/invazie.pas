const mod1=666013;

var t,i,j:longint;
    a,b,n:longint;
    bufin,bufout:array[1..65000]of byte;
    s,st,ab:int64;

begin
  assign(input,'invazie.in'); reset(input);
  assign(output,'invazie.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(t);
  for j := 1 to t do
  begin
    s := 0; st := 0; ab := 0;

    readln(a,b,n);
    ab := a+b;
    st := 1; for i := 1 to n do st := (st * ab)mod mod1;
    s := s + st;
    ab := a-b;
    st := 1; for i := 1 to n do st := (st * ab)mod mod1;
    s := (s + st) mod mod1;
    s := s div 2;

    writeln(s mod mod1);
  end;


  close(input);
  close(output);
end.