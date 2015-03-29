var r:array[1..1000]of longint;
    a:array[1..1000,1..1000]of boolean;
    n,m,i,j,x,y,ramas,t:longint;
    bufin:array[1..65000]of byte;

procedure Rezolva(l,h:longint);
var i,t:longint;
begin
  if ramas > 0 then
  begin
    for i := l to h-1 do
      if a[r[i],r[i+1]] then
      begin
        a[r[i],r[i+1]] := false; dec(ramas);
        t := r[i]; r[i] := r[i+1]; r[i+1] := t;

        {for j := i downto 2 do
        begin
          if not a[r[i],r[i-1]] then break;
          a[r[i],r[i-1]] := false; dec(ramas);
          t := r[i]; r[i] := r[i-1]; r[i-1] := t;
        end;

        for j := i+1 to n-1 do
        begin
          if not a[r[i],r[i+1]] then break;
          a[r[i],r[i+1]] := false; dec(ramas);
          t := r[i]; r[i] := r[i+1]; r[i+1] := t;
        end;   }

      end;

  end;
end;

begin
  assign(input,'inter.in'); reset(input);
  assign(output,'inter.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);

  for i := 1 to n do
    for j := 1 to n do
      a[i,j] := false;

  for i := 1 to n do r[i] := i;

  for i := 1 to m do
  begin
    readln(x,y);
    if x > y then
    begin
      t := x; x := y; y := t;
    end;

    a[x,y] := a[x,y] xor true;
  end;

  ramas := 0;
  for i := 1 to n do
    for j := 1 to n do
      if a[i,j] then inc(ramas);

  repeat
    Rezolva(1,n);
  until ramas = 0 ;

  for i := 1 to n do write(r[i],' ');

  close(input);
  close(output);
end.
