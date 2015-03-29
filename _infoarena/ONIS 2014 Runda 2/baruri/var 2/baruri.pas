var bufin,bufout:array[1..65000]of byte;
    t,ti:longint;
    n,m,i,j:longint;
    r:int64;
    op,b,x,b2:longint;
    s:array[0..1000001]of int64;
 
function max(a,b:longint):longint;
begin
  if a > b then max := a else max := b;
end;
 
function min(a,b:longint):longint;
begin
  if a < b then min := a else min := b;
end;
 
procedure rezolva;
var i,h1,h2:longint;
begin
  r := 0;
  h1 := max(1,b-x); h2 := min(n,b+x);
  r := s[h2] - s[h1-1] - (s[b]-s[b-1]) ;
end;
 
begin
  assign(input,'baruri.in');reset(input);
  assign(output,'baruri.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
 
  s[0] := 0;
 
  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    for i := 1 to n do
    begin
      read(x);
      s[i] := s[i-1] + x;
    end;  readln();
    readln(m);
    for i := 1 to m do
    begin
      read(op);
      case op of
        0:begin
            readln(b,x);
            rezolva;
            writeln(r);
          end;
        1:begin
            readln(x,b);
            for j := b to n do s[j] := s[j] + x;
          end;
        2:begin
            readln(x,b);
            for j := b to n do s[j] := s[j] - x;
          end;
        3:begin
            readln(x,b,b2);
            if b < b2 then
            begin
              for j := b to b2-1 do s[j] := s[j]-x;
            end
            else
            begin
              for j := b2 to b-1 do s[j] := s[j] - x;
            end;
          end;
      end;
    end;
  end;
 
 
  close(input);
  close(output);
end.