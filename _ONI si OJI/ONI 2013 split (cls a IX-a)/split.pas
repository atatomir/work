var n,i,j,min,max:longint;
    a,minst,mindr,maxst,maxdr:array[0..5010]of longint;
    bufin:array[1..65000]of byte;
    solmax,solt,solt2,c1,c2,c3,d1,d2,d3,solst:longint;

begin
  assign(input,'split.in'); reset(input);
  assign(output,'split.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  read(a[1]); minst[1] := a[1]; maxst[1] := a[1];
  for i := 2 to n do      // calculeaza min max st
  begin
    read(a[i]);
    if a[i] > maxst[i-1] then maxst[i] := a[i] else maxst[i] := maxst[i-1];
    if a[i] < minst[i-1] then minst[i] := a[i] else minst[i] := minst[i-1];
  end;

  mindr[n] := a[n]; maxdr[n] := a[n];
  for i := n-1 downto 1 do
  begin
    if a[i] > maxdr[i+1] then maxdr[i] := a[i] else maxdr[i] := maxdr[i+1];
    if a[i] < mindr[i+1] then mindr[i] := a[i] else mindr[i] := mindr[i+1];
  end;

  // OK

  solmax := -1; c1 := -1; c2 := -1; c3 := -1;
  solt := -1; solt2 := -1; solst := -1;
                             // calcul stanga
  for i := 4 to n - 3 do
  begin
    if a[i]> a[i-1] then
    begin
      min := a[i-1];
      max := a[i];
    end
    else
    begin
      min := a[i];
      max := a[i-1];
    end;
    solt := max-min + maxst[i-2] - minst[i-2];  d1 := j-2;

    for j :=  i-2 downto 3 do
    begin
      if a[j] > max then max := a[j];
      if a[j] < min then min := a[j];
      solt2 := max - min + maxst[j-1] - minst[j-1];
      if solt <= solt2 then
      begin
        solt := solt2;
        d1 := j-1;
      end;
    end;

    d2 := i;
    solst := solt;

                           //calcul dreapta
    if a[i+1] > a[i+2] then
    begin
      max := a[i+1];
      min := a[i+2];
    end
    else
    begin
      max := a[i+2];
      min := a[i+1];
    end;
    solt := max - min + maxdr[i+3] - mindr[i+3];

    for j := i+3 to n-2 do
    begin
      if a[j] > max then max := a[j];
      if a[j] < min then min := a[j];
      solt2 := max - min + maxdr[j+1] - mindr[j+1];
      if solt < solt2 then
      begin
        solt := solt2;
        d3 := j;
      end;
    end;

    solst := solst + solt;
    if solmax < solst then
    begin
      solmax := solst;
      c1 := d1;
      c2 := d2;
      c3 := d3;
    end;
  end;

  writeln(solmax);
  writeln(c1,' ',c2,' ',c3);

  close(input);
  close(output);
end.
