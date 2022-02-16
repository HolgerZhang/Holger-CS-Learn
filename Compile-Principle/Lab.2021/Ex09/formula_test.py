import unittest

from formula import atom_count


class FormulaTestCase(unittest.TestCase):
    def test_something(self):
        formulas = [('He', 1), ('H2', 2), ('H2SO4', 7), ('CH3COOH', 8), ('NaCl', 2), ('C60H60', 120)]
        for formula, count in formulas:
            result = atom_count(formula)
            print(result)
            self.assertIsNotNone(result)
            self.assertEqual(result.atom_count, count)


if __name__ == '__main__':
    unittest.main()
