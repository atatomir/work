var n,m,i,j:longint;
    a:array[0..130,0..130]of word;
    r:array[0..130,0..130,1..2]of word;
    bufin:array[1..65000]of byte;
    max,maxs:word;

procedure Recurs(i,j,pas,val:word);
var mini,minj:word;
begin
  if (r[i,j,1] < pas) then
  begin
    r[i,j,1] := pas;
    r[i,j,2] := val;

  mini := i-1; minj := j;

  if a[i+1,j] < a[mini,minj] then begin mini := i+1; minj := j;   end;
  if a[i,j-1] < a[mini,minj] then begin mini := i;   minj := j-1; end;
  if a[i,j+1] < a[mini,minj] then begin mini := i;   minj := j+1; end;

  if a[mini,minj] < a[i,j] then
    Recurs(mini,minj,pas+1,val);

  end;

end;

begin
  assign(input,'bila.in'); reset(input);
  assign(output,'bila.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(a[i,j]); r[i,j,1] := 0;
    end;
    readln();
  end;

  for i := 0 to n+1 do
  begin
    a[i,0] := 65005; a[i,m+1] := 65005;
    r[i,0,1] := 65005; r[i,m+1,1] := 65005;
  end;
  for i := 0 to m+1 do
  begin
    a[0,i] := 65005; a[n+1,i] := 65005;
    r[0,i,1] := 65005; r[n+1,i,1] := 65005;
  end;

  for i := 1 to n do
    for j := 1 to m do
      if r[i,j,1] = 0 then
        Recurs(i,j,1,a[i,j]);

  max := 0;

  for i := 1 to n do
    for j := 1 to m do
      if (max < r[i,j,1])or((max=r[i,j,1])and(maxs > r[i,j,2])) then
      begin
        max := r[i,j,1];
        maxs := r[i,j,2];
      end;

  writeln(max,' ',maxs);



  close(input);
  close(output);
end.
