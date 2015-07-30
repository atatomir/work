var r,s,a:array[0..105,0..105]of longint;
    n,m,i,j,ant,x,ii,jj,h1,h2,max,maxi,maxj,maxii,maxjj:longint;

function Verif(i,j,ii,jj:longint):boolean;
var t:longint;
begin
  verif := true;
  for t := i to i+ii-1 do
  begin
    if r[t,j+jj-1] - r[t,j] <> jj-1 then
    begin
      verif := false;
      break;
    end;
  end;

  if verif then
  for t := j to j+jj-1 do
  begin
    if s[i+ii-1,t] - s[i,t] <> ii-1 then
    begin
      verif := false;
      break;
    end;
  end;

  //writeln(i,' ',j,' ',ii,' ',jj,' ',verif);
end;

begin
  assign(input,'matrice.in'); reset(input);
  assign(output,'matrice.out'); rewrite(output);

  readln(n,m);
  for i := 1 to n do
  begin
    read(ant); r[i,1] := 0;  a[i,1] := ant;
    for j := 2 to m do
    begin
      read(x);  a[i,j] := x;
      if ant <= x then
        r[i,j] := r[i,j-1] +1;
      ant := x;
    end;
    readln();
  end;

  for j := 1 to m do
  begin
    ant := a[1,j]; s[1,j] := 0;
    for i := 2 to n do
    begin
      if ant <= a[i,j] then
        s[i,j] := s[i-1,j]+1;
      ant := a[i,j];
    end;
  end;

  for i := 0 to m+1 do r[0,i] := 0;
  for i := 0 to n+1 do r[i,0] := 0;

  {for i := 1 to n do
  begin
    for j := 1 to m do write(s[i,j],' ');
    writeln();
  end;      }

  max := 0; maxi := 0; maxii := 0; maxj := 0; maxjj := 0;

  for i := 1 to n do
    for j := 1 to m do
    begin
      h1 := n-i; h2 := m-j;
      for ii := 1 to i+h1 do
        for jj := 1 to j+h2 do
        begin
          if ii*jj > max then
          begin
            if Verif(i,j,ii,jj) then
            begin
              max := ii*jj;
              maxi := i; maxj := j;
              maxii := ii; maxjj := jj;
            end;

          end;
        end;

    end;

  writeln(maxii,' ',maxjj);
  for i := maxi to maxi+maxii-1 do
  begin
    for j := maxj to maxj+maxjj-1 do
      write(a[i,j],' ');
    writeln();
  end;




  close(input);
  close(output);
end.
