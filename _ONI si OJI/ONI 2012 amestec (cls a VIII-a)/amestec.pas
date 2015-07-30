var n,k,i,j,t,timp:longint;
    a:array[0..100,0..100]of byte;
    sum:array[1..2,1..100]of byte;
    c,dir:char;
    s:string;


procedure Rezolva(dir:char);
var i,j:longint;
    sari:boolean;
begin
  case dir of
    'N':begin
          for i := 1 to n do
          begin
            sari := false;
            for j := n downto 2 do
            begin
              if sari then
                sari := false
              else
              begin
                if (a[j,i] = 1) and (a[j-1,i] = 0) then
                begin
                  sari := true;
                  a[j,i] := 0; a[j-1,i] := 1;
                  dec(sum[1,j]); inc(sum[1,j-1]);
                end;
              end;
            end;
          end;
        end;
    'S':begin
          for i := 1 to n do
          begin
            sari := false;
            for j := 1 to n-1 do
            begin
              if sari then
                sari := false
              else
              begin
                if (a[j,i] = 1) and (a[j+1,i] = 0) then
                begin
                  sari := true;
                  a[j,i] := 0; a[j+1,i] := 1;
                  dec(sum[1,j]); inc(sum[1,j+1]);
                end;
              end;
            end;
          end;
        end;
    'E':begin
          for i := 1 to n do
          begin
            sari := false;
            for j := 1 to n-1 do
            begin
              if sari then
                sari := false
              else
              begin
                if (a[i,j] = 1) and (a[i,j+1] = 0) then
                begin
                  sari := true;
                  a[i,j] := 0; a[i,j+1] := 1;
                  dec(sum[2,j]); inc(sum[2,j+1]);
                end;
              end;
            end;
          end;
        end;
    'V':begin
          for i := 1 to n do
          begin
            sari := false;
            for j := n downto 2 do
            begin
              if sari then
                sari := false
              else
              begin
                if (a[i,j] = 1) and (a[i,j-1] = 0) then
                begin
                  sari := true;
                  a[i,j] := 0; a[i,j-1] := 1;
                  dec(sum[2,j]); inc(sum[2,j-1]);
                end;
              end;
            end;
          end;
        end;
  end;
end;

procedure Do_sum;
var i,j:longint;
begin
  for i := 1 to n do
  begin
    sum[1,i] := 0;
    sum[2,i] := 0;
  end;

  for i := 1 to n do
    for j := 1 to n do
    begin
      if a[i,j] = 1 then
      begin
        inc(sum[1,i]);
        inc(sum[2,j]);
      end;
    end;

end;

begin
  assign(input,'amestec.in'); reset(input);
  assign(output,'amestec.out'); rewrite(output);

  readln(n,k);

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(c);
      if c = '0' then
        a[i,j] := 0
      else
        a[i,j] := 1;
    end;
    readln();
  end;

  Do_sum;

  for t := 1 to k do
  begin
    readln(s);
    i := 1;
    timp := 0;
    while pos(s[i],'0123456789') > 0 do
    begin
      timp := timp * 10 + ord(s[i])- 48;
      inc(i);
    end;
    dir := s[i];
    c := s[i+1];

    if c = '0' then
    begin
      case dir of
        'N': dir := 'S';
        'S': dir := 'N';
        'E': dir := 'V';
        'V': dir := 'E';
      end;
    end;


    if timp >= n-1 then
    begin

      case dir of
        'N':begin
              for j := 1 to n do
              begin
                for i := 1 to sum[2,j] do
                  a[i,j] := 1;
                for i := sum[2,j]+1 to n do
                  a[i,j] := 0;
              end;
            end;
        'S':begin
              for j := 1 to n do
              begin
                for i := n downto n-sum[2,j]+1 do
                  a[i,j] := 1;
                for i := 1 to n-sum[2,j] do
                  a[i,j] := 0;
              end;
            end;
        'E':begin
              for i:= 1 to n do
              begin
                for j := 1 to n-sum[1,i] do
                  a[i,j] := 0;
                for j := n-sum[1,i]+1 to n do
                  a[i,j] := 1;
              end;
            end;
        'V':begin
              for i := 1 to n do
              begin
                for j := 1 to sum[1,i] do
                  a[i,j] := 1;
                for j := sum[1,i]+1 to n do
                  a[i,j] := 0;
              end;
            end;
        end;
        Do_sum;
    end
    else
      for i := 1 to timp do Rezolva(dir);

  end;

  for i := 1 to n do
  begin
    for j := 1 to n do write(a[i,j]);
    writeln();
  end;

  close(input);
  close(output);
end.