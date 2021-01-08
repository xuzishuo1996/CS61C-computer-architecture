#!/usr/bin/env python

import os
import os.path
import tempfile
import subprocess
import time
import signal
import re
import sys
import shutil

#("ALU comprehensive test", "student_output/alu-comprehensive-student.out", TestCase(os.path.join(file_locations,'alu_tests/alu-comprehensive.circ'), os.path.join(file_locations,'reference_output/alu-comprehensive-ref.out'), "Reference columns are Test #, Result1")

file_locations = os.path.expanduser(os.getcwd())
logisim_location = os.path.join(os.getcwd(),"logisim-evolution.jar")

class TestCase():
  """
      Runs specified circuit file and compares output against the provided reference trace file.
  """

  def __init__(self, circfile, tracefile, register_doc):
    self.circfile  = circfile
    self.tracefile = tracefile
    self.register_doc = register_doc

  def __call__(self, filename):
    output = tempfile.TemporaryFile(mode='r+')
    proc = subprocess.Popen(["java","-jar",logisim_location,"-tty","table",self.circfile],
                            stdin=open('/dev/null'),
                            stdout=subprocess.PIPE)
    try:
      reference = open(self.tracefile)
      passed = compare_unbounded(proc.stdout,reference, filename)
    finally:
      os.kill(proc.pid,signal.SIGTERM)
    if passed:
      return (True, "Matched expected output")
    else:
      return (False, "Did not match expected output: " + self.register_doc)

def compare_unbounded(student_out, reference_out,filename):
  passed = True
  student_output_array = []
  while True:
    line1 = student_out.readline()
    line2 = reference_out.readline()
    if line2 == '':
      break
    line1 = line1.decode('utf-8')
    student_output_array.append(line1)
    m = re.match(line2, line1)
    if m == None or m.start() != 0 or m.end() != len(line2):
      passed = False
  with open(filename, "w") as student_output:
    for line in student_output_array:
      student_output.write(line)
  return passed


def run_tests(tests):
  print("Testing files...")
  tests_passed = 0
  tests_failed = 0

  for description,filename,test in tests:
    test_passed, reason = test(filename)
    if test_passed:
      print("\tPASSED test: %s" % description)
      tests_passed += 1
    else:
      print("\tFAILED test: %s (%s)" % (description, reason))
      tests_failed += 1
  
  print("Passed %d/%d tests" % (tests_passed, (tests_passed + tests_failed)))

tests = [
  ("ALU add test", "student_output/alu-add-student.out",TestCase(os.path.join(file_locations,'alu_tests/alu-add.circ'), os.path.join
(file_locations,'reference_output/alu-add-ref.out'), "Reference columns are Test #, Result1")),
  ("ALU multiply test", "student_output/alu-mult-student.out", TestCase(os.path.join(file_locations,'alu_tests/alu-mult.circ'), os.path.join(file_locations,'reference_output/alu-mult-ref.out'), "Reference columns are Test #, Result1")),
  ("ALU div and rem test", "student_output/alu-div-rem-student.out", TestCase(os.path.join(file_locations,'alu_tests/alu-div-rem.circ'), os.path.join(file_locations,'reference_output/alu-div-rem-ref.out'), "Reference columns are Test #, Result1")),
  ("ALU logic test", "student_output/alu-logic-student.out", TestCase(os.path.join(file_locations,'alu_tests/alu-logic.circ'), os.path.join(file_locations,'reference_output/alu-logic-ref.out'), "Reference columns are Test #, Result1")),
  ("ALU shift test", "student_output/alu-shift-student.out", TestCase(os.path.join(file_locations,'alu_tests/alu-shift.circ'), os.path.join(file_locations,'reference_output/alu-shift-ref.out'), "Reference columns are Test #, Result1")),
  ("ALU select, sub, BSel test", "student_output/alu-set-sub-bsel-student.out", TestCase(os.path.join(file_locations,'alu_tests/alu-set-sub-bsel.circ'), os.path.join(file_locations,'reference_output/alu-set-sub-bsel-ref.out'), "Reference columns are Test #, Result1")),
 ("RegFile insert test", "student_output/regfile-insert-student.out", TestCase(os.path.join(file_locations,'regfile_tests/regfile-insert.circ'), os.path.join(file_locations,'reference_output/regfile-insert-ref.out'), "Reference columns are Test #, ra, sp, t0, t1, t2, s0, s1, a0, Read Data 1, Read Data 2")), 
  ("RegFile zero test", "student_output/regfile-zero-student.out", TestCase(os.path.join(file_locations,'regfile_tests/regfile-zero.circ'), os.path.join(file_locations,'reference_output/regfile-zero-ref.out'), "Reference columns are Test #, ra, sp, t0, t1, t2, s0, s1, a0, Read Data 1, Read Data 2")),
  ("RegFile x0 test", "student_output/regfile-x0-student.out", TestCase(os.path.join(file_locations,'regfile_tests/regfile-x0.circ'), os.path.join(file_locations,'reference_output/regfile-x0-ref.out'), "Reference columns are Test #, ra, sp, t0, t1, t2, s0, s1, a0, Read Data 1, Read Data 2")),
  ("RegFile all registers test", "student_output/regfile-allregs-student.out", TestCase(os.path.join(file_locations,'regfile_tests/regfile-allregs.circ'), os.path.join(file_locations,'reference_output/regfile-allregs-ref.out'), "Reference columns are Test #, ra, sp, t0, t1, t2, s0, s1, a0, Read Data 1, Read Data 2"))

]

if __name__ == '__main__':
  run_tests(tests)
