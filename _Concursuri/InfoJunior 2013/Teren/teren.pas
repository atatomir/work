var n,m,i,j,sol,i1,i2,j1,j2,t,max:longint;
    a:array[0..303,0..303]of byte;
    s1,s2,s3:boolean;
    bufin:array[1..65000]of byte;

begin
  assign(input,'teren.in'); reset(input);
  assign(output,'teren.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,sol);

  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(a[i,j]);
    end;
    readln();
  end;


  max := 0;
  for t := 1 to sol do
  begin
    readln(i1,j1,i2,j2);
    s1 := false; s2 := false; s3 := false;
    for i := i1 to i2 do
    begin
      for j := j1 to j2 do
      begin
        case a[i,j] of
          1: s1 := true;
          2: s2 := true;
          3: s3 := true;
          4: begin
               s1 := true;
               s2 := true;
             end;
          5: begin
               s1 := true;
               s3 := true;
             end;
          6: begin
               s2 := true;
               s3 := true;
             end;
          7: begin
               s1 := true;
               s2 := true;
               s3 := true;
               break;
             end;
        end;

      end;
      if (s1 = true) and (s2 = true) and (s3 = true) then
      begin
        inc(max);
        break;
      end;
    end;

  end;

  writeln(max);


  close(input);
  close(output);
end.
