var bufin:array[1..65000]of byte;
    n,i,j:longint;
    sir:array[1..1000000]of longint;
    imax,jmax:longint;
    max,ort,andt,suma:longint;

begin
  assign(input,'sushi.in'); reset(input);
  assign(output,'sushi.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do read(sir[i]);

  max := 0;

  for i := 1 to n do
  begin
    ort := sir[i];
    andt := sir[i];
    for j := i to n do
    begin
      ort := ort or sir[j] ;
      andt := andt and sir[j] ;
      suma := ort + andt;
      if suma >= max then
      begin
        if suma > max then
        begin
          imax := i ;
          jmax := j ;
          max := suma;
        end
        else
        begin
          if imax = i then
          begin
            jmax := j;
            max := suma;
          end
        end;
      end;

    end;
  end;

  write(imax,' ',jmax,' ',max);

  close(input);
  close(output);
end.
