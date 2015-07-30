var n,b,k,i,j,pos,max:longint;
    s:ansistring;
    a:array[0..10005,0..3]of longint;
    bufin:array[1..65000]of byte;

procedure readnr(dest:longint);
begin
  while s[pos] <> ' ' do begin inc(a[dest,ord(s[pos])- $30]); inc(pos); end;
  inc(pos);
end;

procedure verif(var maxim,minim:longint;g:longint);inline;
begin
  if g > maxim then maxim := g else
  if g < minim then minim := g;
end;

procedure Rezolva(pas,sel,n0,n1,n2,n3:longint);
var i,nmax,nmin:longint;
    ok:boolean;
begin
  if pas = n+1 then
  begin
    ok := true;
    case b of
      2: if n0 <> n1 then ok := false;
      3: if (n0<>n1)or(n1<>n2) then ok := false;
      4: if (n0<>n1)or(n1<>n2)or(n2<>n3) then ok := false;
    end;
    if ok then
      if sel > max then max := sel;
  end
  else
  begin
    Rezolva(pas+1,sel,n0,n1,n2,n3);
    n0 := n0 + a[pas,0]; nmax := n0; nmin := n0;
    n1 := n1 + a[pas,1]; if b >1 then verif(nmax,nmin,n1);
    n2 := n2 + a[pas,2]; if b >2 then verif(nmax,nmin,n2);
    n3 := n3 + a[pas,3]; if b >3 then verif(nmax,nmin,n3);

    if nmax - nmin <= k then Rezolva(pas+1,sel+1,n0,n1,n2,n3);
  end;

end;

begin
  assign(input,'ssce.in'); reset(input);
  assign(output,'ssce.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,b,k);
  readln(s); s := s + ' ';

  for i := 1 to n do
  begin
    for j := 0 to b-1 do a[i,j] := 0;
  end;

  pos := 1;
  for i := 1 to n do readnr(i);

  max := 0;
  Rezolva(1,0,0,0,0,0);

  writeln(max);

  close(input);
  close(output);
end.
