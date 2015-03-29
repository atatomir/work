var bufin,bufout:array[1..65000]of byte;
    t,ti:longint;
    n,m,i,j:longint;
    r:int64;
    a:array[0..100001]of longint;
    op,b,x,b2:longint;
 
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
  for i := h1 to b-1 do r := r + a[i];
  for i := b+1 to h2 do r := r + a[i];
end;
 
begin
  assign(input,'baruri.in');reset(input);
  assign(output,'baruri.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);
 
 
  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    for i := 1 to n do read(a[i]); readln();
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
            a[b] := a[b] + x;
          end;
        2:begin
            readln(x,b);
            a[b] := a[b] - x;
          end;
        3:begin
            readln(x,b,b2);
            a[b] := a[b] - x;
            a[b2] := a[b2] + x;
          end;
      end;
    end;
  end;
 
 
  close(input);
  close(output);
end.