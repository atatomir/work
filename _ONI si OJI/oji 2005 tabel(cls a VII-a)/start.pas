program tabel;

var a:array[1..50,1..50] of integer;
    n,m:byte;
    p:integer;
    k:integer;
    dl,dc:array[1..50] of byte;

procedure citeste;
var f:text;
    i:integer;
    x1,x2:byte;
begin
  assign(f,'tabel.in'); reset(f);
  readln(f,n,m);
  readln(f,p);
  fillchar(a,sizeof(a),-1);
  k:= n*m;
  fillchar(dl,sizeof(dl),m);
  fillchar(dc,sizeof(dc),n);
  for i := 1 to p do
  begin
    readln(f,x1,x2,a[x1,x2]);
    dec(k);
    dec(dl[x1]);
    dec(dc[x2]);
  end;
  close(f);
end;

procedure scrie_sol;
var i,j:byte;
    fo:text;
begin
  assign(fo,'tabel.out'); rewrite(fo);
  if k > 0 then write(fo,'Nu') else
  begin
    for i := 1 to n do
    begin
      for j := 1 to m do
      begin
        write(fo,a[i,j],' ');
      end;
      writeln(fo);
    end;
  end;
  close(fo);
end;

procedure rezolva_linia(x:Integer);
var retin,i:byte;
    s:longint;
begin
 s := 0;
 retin := 0;

 for i := 1 to m-1 do
   if a[x,i]=-1 then begin retin := i; end else s := s + a[x,i];
 if a[x,m]=0 then a[x,m] := s else a[x,retin]:= a[x,m]-s;
 dec(k);
 dec(dl[x]);
 dec(dc[retin]);
end;

procedure rezolva_coloana(x:Integer);
var retin,i:byte;
    s:longint;
begin
 s := 0;
 retin := 0;

 for i := 1 to n-1 do
   if a[i,x]=-1 then begin retin := i; end else s := s + a[i,x];
 if a[n,x]=0 then a[n,x] := s else a[retin,x]:= a[n,x]-s;
 dec(k);
 dec(dl[x]);
 dec(dc[retin]);
end;

procedure rezolva;
var i:byte;
    ok:boolean;

begin
  ok := false;
  while (k>0) and (ok=false) do
  begin
    ok := true;
    for i := 1 to n do if dl[i]=1 then begin ok := false; rezolva_linia(i); end;
    for i := 1 to m do if dc[i]=1 then begin ok := false; rezolva_coloana(i); end;
  end;
end;





begin
citeste;
rezolva;
scrie_sol;
end.



