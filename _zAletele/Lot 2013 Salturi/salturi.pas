var n,i,j,pozmin:longint;
    a,r:array[1..1000000]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'salturi.in'); reset(input);
  assign(output,'salturi.out'); rewrite(output);
  settextbuf(Input,bufin);

  readln(n);
  for i := 1 to n do
  begin
    read(a[i]);
    r[i] := 0;
  end;

  pozmin := 0;

  for i := 1 to n do
  begin
    if a[i] > 0 then
    begin
      if pozmin <= i then pozmin := i+1;
      if i + a[i] > n then
      begin
        writeln(r[i]+1);
        close(input); close(output);
        exit;
      end;
      for j := pozmin to i + a[i] do r[j] := r[i] + 1;
      if pozmin < i + a[i]+1 then pozmin := i+a[i]+1;
    end;


  end;



end.
