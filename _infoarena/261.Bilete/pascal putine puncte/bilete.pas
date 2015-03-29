var n,k,j,i,h,u,v,s,t:smallint;
    bufout:array[1..65000]of byte;

begin
  assign(input,'bilete.in'); reset(input);
  assign(output,'bilete.out'); rewrite(output);
  settextbuf(output,bufout);

  read(n,k);

  if k =1 then
  begin
    for i := 1 to n do
    begin
      h := (n+1) div 2;
      for j := 1 to h do
      begin
        writeln(i,j);
      end;
    end;
  end
  else
  if k = 2 then
  begin
    for i := 1 to n do
    begin
      h := (n+1) div 2;
      for j := 1 to h do
      begin
        for u := j+1 to n-j+1 do    //completeaza randul
        begin
          writeln(i,j,i,u);
        end;                        //e completeaza randul

        if (n mod 2 = 0) or (j<>h) then
        begin
          for u := i + 1 to n do      //completeaza restul randurilor(j nu e la mijloc)
          begin
            for v := 1 to n do
            begin
              writeln(i,j,u,v);
            end;
          end;                //e completeaza restul randurilor
        end
        else
        begin                 // complet restul randurilor (j la mijloc)
          for u := i + 1 to n do
          begin
            for v := 1 to h do
            begin
              writeln(i,j,u,v);
            end;
          end;
        end;                  //e completeaza restul randurilor
      end;
    end;
  end
  else
  begin
    for i := 1 to n do
    begin
      h := (n+1) div 2;
      for j := 1 to h do
      begin
        for u := j+1 to n-j+1 do    //completeaza randul
        begin
          for s := u+1 to n do
          begin
            writeln(i,j,i,u,i,s);
          end;
        end;                        //e completeaza randul

        if (n mod 2 = 0) or (j<>h) then
        begin
          for u := i + 1 to n do      //completeaza restul randurilor(j nu e la mijloc)
          begin
            for v := 1 to n do
            begin
              for s := u +1 to n do
              begin
                for t := 1 to n do
                begin
                  writeln(i,j,u,v,s,t);
                end;
              end;
            end;
          end;                //e completeaza restul randurilor
        end
        else
        begin                 // complet restul randurilor (j la mijloc)
          for u := i + 1 to n do
          begin
            for v := 1 to h do
            begin
              if (n mod 2 = 0) or (v<>h) then
              begin
                for s := u +1 to n do
                begin
                  for t := 1 to n do
                  begin
                    writeln(i,j,u,v,s,t);
                  end;
                end;
              end
              else
              begin
                for s := u +1 to n do
                begin
                  for t := 1 to h do
                  begin
                    writeln(i,j,u,v,s,t);
                  end;
                end;
              end;
            end;
          end;
        end;                  //e completeaza restul randurilor
      end;
    end;





  end;



  close(input);
  close(output);
end.
