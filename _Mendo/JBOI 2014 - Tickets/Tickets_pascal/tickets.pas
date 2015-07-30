var i:longint;
    n,k,put:int64;


begin
  readln(n,k);

  put := 1;
  for i := 1 to n-1 do put := 2*put;

  for i := 1 to n do
  begin
    if k <= put then
    begin
      write(0);
    end
    else
    begin
      write(1);
      k := k - put;
      k := put - k + 1;

    end;
    put := put shr 1;
  end;



end.
