type stiva = record
       i,j:longint;
     end;
var op:longint;
    n,k,i,si,x,y,xx,yy,max:longint;
    bufin:array[1..65000]of byte;
    a:array[1..5000]of longint;
    b:array[1..1000]of longint;
    s:array[1..5000]of stiva;
    ok:boolean;

procedure Rez_1;
var min:longint;
    ok:boolean;
begin
  for i := 1 to 1000 do b[i] := 0;   min := a[1];
  for i := 1 to k do
  begin
    inc(b[a[i]]);
    if a[i] < min then min := a[i];
  end;

  ok := true;
  for i := min to min+k-1 do
    if b[i] <> 1 then
    begin
      ok := false;
      break;
    end;

  if ok then
    writeln(min+k-1)
  else
  begin
    min := 0;
    for i := 1 to 1000 do
      if b[i] = 1 then inc(min);
    writeln(min);
  end;

end;

procedure get(var x,y:longint);
begin
  if si > 0 then
  begin
    x := s[si].i; y := s[si].j;
    dec(si);
  end
  else
  begin
    x := -1; y := -1;
  end;
end;

procedure put(x,y:longint);
begin
  inc(si);
  s[si].i := x; s[si].j := y;
end;

function Verif(min,k:longint):boolean;
var i:longint;
begin
  verif := true;
  for i := min to min+k-1 do
    if b[i] <> 1 then
    begin
      verif := false;
      break;
    end;


end;

function Cauta(k:longint):longint;
var i,j,min:longint;
begin
  for i := 1 to 1000 do b[i] := 0; min := a[1]; cauta := 0;
  for i := 1 to k do
  begin
    inc(b[a[i]]);
    if min > a[i] then min := a[i];
  end;

  if Verif(min,k) then inc(cauta); i := 1;
  for j := k+1 to n do
  begin
    dec(b[a[i]]); inc(i);
    if min=a[i] then
      while b[min] = 0 do inc(min);

    inc(b[a[j]]);
    if min > a[j] then min := a[j];


    if Verif(min,k) then inc(cauta);
  end;


end;

begin
  assign(input,'cool.in'); reset(input);
  assign(output,'cool.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(op);
  readln(n,k);
  for i := 1 to n do read(a[i]);

  if op = 1 then
    Rez_1
  else
  begin
    si := 0;
    for i := 1 to n do
    begin
      x := a[i]; y := a[i];
      ok := true;
      while ok do
      begin
        get(xx,yy); if xx = -1 then break;
        if y+1 = xx then
          y := yy
        else
        if x = yy+1 then
          x := xx
        else
          ok := false;
      end;

      if ok then
        put(x,y)
      else
      begin
        put(xx,yy);
        put(x,y);
      end;
    end;

    max := s[1].j-s[1].i+1;

    for i := 2 to si do
      if max < s[i].j-s[i].i+1 then
        max :=s[i].j-s[i].i+1;

    //for i := 1 to si do writeln(s[i].i,' ',s[i].j);

    writeln(max);

    writeln(Cauta(max));


  end;






  close(input);
  close(output);
end.
