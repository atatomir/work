var bufin:array[1..65000]of byte;
    a:array[1..241,1..241]of longint;
    n,i,j,max,h:longint;

begin
  assign(input,'sotron.in'); reset(input);
  assign(output,'sotron.out'); rewrite(output);
  settextbuf(input,bufin);

  max := -1000000000;

  readln(n);

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(a[n-i+1,j]);
    end;
    readln();
  end;

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      h := n-i+1 + j;
      if h mod 2 = 0 then   //daca vine din stanga
      begin
        if j-1 >= 1 then
        begin
          if a[i,j] + a[i,j-1] > a[i,j] then
            a[i,j] := a[i,j] + a[i,j-1];
        end;
        //if max < a[i,j] then max := a[i,j];
      end
      else
      begin                 // daca vine de sus
        if i-1 >= 1 then
        begin
          if a[i,j] + a[i-1,j] > a[i,j] then
            a[i,j] := a[i,j] + a[i-1,j];
        end;
        //if max < a[i,j] then max := a[i,j];
      end;

      if max < a[i,j] then max := a[i,j];
    end;
  end;


  write(max);

  close(input);
  close(output);
end.
