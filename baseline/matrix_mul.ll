; ModuleID = 'matrix_mul.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: nounwind
define void @_Z10matrix_mulPfS_S_j(float* nocapture readonly %sq_matrix_1, float* nocapture readonly %sq_matrix_2, float* nocapture %sq_matrix_result, i32 %sq_dimension) #0 {
entry:
  %cmp42 = icmp eq i32 %sq_dimension, 0
  br i1 %cmp42, label %for.end20, label %for.cond4.preheader.lr.ph

for.cond4.preheader.lr.ph:                        ; preds = %for.inc18, %entry
  %i.043 = phi i32 [ %inc19, %for.inc18 ], [ 0, %entry ]
  %mul = mul i32 %i.043, %sq_dimension
  br label %for.body6.lr.ph

for.body6.lr.ph:                                  ; preds = %for.end, %for.cond4.preheader.lr.ph
  %j.041 = phi i32 [ 0, %for.cond4.preheader.lr.ph ], [ %inc16, %for.end ]
  br label %for.body6

for.body6:                                        ; preds = %for.body6, %for.body6.lr.ph
  %k.038 = phi i32 [ 0, %for.body6.lr.ph ], [ %inc, %for.body6 ]
  %sum.037 = phi float [ 0.000000e+00, %for.body6.lr.ph ], [ %add11, %for.body6 ]
  %add = add i32 %k.038, %mul
  %arrayidx = getelementptr inbounds float* %sq_matrix_1, i32 %add
  %0 = load float* %arrayidx, align 4, !tbaa !1
  %mul7 = mul i32 %k.038, %sq_dimension
  %add8 = add i32 %mul7, %j.041
  %arrayidx9 = getelementptr inbounds float* %sq_matrix_2, i32 %add8
  %1 = load float* %arrayidx9, align 4, !tbaa !1
  %mul10 = fmul float %0, %1
  %add11 = fadd float %sum.037, %mul10
  %inc = add i32 %k.038, 1
  %exitcond = icmp eq i32 %inc, %sq_dimension
  br i1 %exitcond, label %for.end, label %for.body6

for.end:                                          ; preds = %for.body6
  %add13 = add i32 %j.041, %mul
  %arrayidx14 = getelementptr inbounds float* %sq_matrix_result, i32 %add13
  store float %add11, float* %arrayidx14, align 4, !tbaa !1
  %inc16 = add i32 %j.041, 1
  %exitcond44 = icmp eq i32 %inc16, %sq_dimension
  br i1 %exitcond44, label %for.inc18, label %for.body6.lr.ph

for.inc18:                                        ; preds = %for.end
  %inc19 = add i32 %i.043, 1
  %exitcond45 = icmp eq i32 %inc19, %sq_dimension
  br i1 %exitcond45, label %for.end20, label %for.cond4.preheader.lr.ph

for.end20:                                        ; preds = %for.inc18, %entry
  ret void
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"float", metadata !3, i64 0}
!3 = metadata !{metadata !"omnipotent char", metadata !4, i64 0}
!4 = metadata !{metadata !"Simple C/C++ TBAA"}
