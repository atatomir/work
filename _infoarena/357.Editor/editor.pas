var bufin:array[1..65000]of byte;
    t:integer;
    i,j,h,drept,desc:longint;
    s:string;
    back,iesi:boolean;
    backi:longint;

begin
  assign(input,'editor.in'); reset(input);
  assign(output,'editor.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for i := 1 to t do
  begin
    drept := 0;
    desc := 0;   iesi := false;

    readln(s);
    h:= length(s);
    for j := 1 to h do
    begin
      case s[i] of
      '[':begin
            back := false;
            inc(drept);
          end;
      ']':begin
            dec(drept);
            if drept < 0 then
            begin
              iesi := true;
            end;
            back := false;
          end;
      '(':begin
            inc(desc);
            back := false;
          end;
      ')':begin
            dec(desc);
            if desc < 0 then
            begin
              iesi := true;
            end;
            back := false;
          end;
      '*':begin
            if back = false then
            begin
              back := true;
              backi := j-1;
              if backi > 0 then
              begin
                case s[backi] of
                  '[': dec(drept);
                  ']': inc(drept);
                  '(': dec(desc);
                  ')': inc(desc);
                end;
                if iesi = true then
                  if (drept >=0) and (desc >= 0) then
                    iesi := false;
              end;
            end
            else
            begin
              dec(backi);
              if backi > 0 then
              begin
                case s[backi] of
                  '[': dec(drept);
                  ']': inc(drept);
                  '(': dec(desc);
                  ')': inc(desc);
                end;
                if iesi = true then
                  if (drept >=0) and
              end;
            end;
          end;
      'E':begin

          end;
      end;
    end;

  end;

  close(input);
  close(output);
end.
