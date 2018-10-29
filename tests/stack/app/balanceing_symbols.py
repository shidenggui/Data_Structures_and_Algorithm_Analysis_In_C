import unittest


class BalanceSymbolsChecker:
    def __init__(self):
        self.allowed_symbols = set('(){}[]')
        self.symbols_type = {
            '(': 'left',
            ')': 'right',
            '{': 'left',
            '}': 'right',
            '[': 'left',
            ']': 'right',
        }
        self.symbols_counterpart = {
         ')': '(',
         '}': '{',
         ']': '[',
        }
    def check(self, content):
        stack = []
        for idx, char in enumerate(content):
            if char not in self.allowed_symbols:
                continue
            if self.symbols_type[char] == 'left':
                stack.append(char)
                continue
            if len(stack) == 0:
                raise ValueError('stack is empty, cant find counterpart for {} at idx {}'.format(char, idx))
            counterpart = stack.pop()
            if counterpart != self.symbols_counterpart[char]:
                raise ValueError('element {} poped from stack is not counterpart for {} at idx {}'.format(counterpart, char, idx))
        if len(stack) != 0:
            raise ValueError('after scan, stack is not empty, still has not balanced symbols: {}'.format(stack))

class TestBalanceSymbolsChecker(unittest.TestCase):
    def test_checker(self):
        checker = BalanceSymbolsChecker()

        with self.assertRaisesRegex(ValueError, 'stack is not empty'):
            checker.check('(')

        with self.assertRaisesRegex(ValueError, 'not counterpart'):
            checker.check('()[)')

        with self.assertRaisesRegex(ValueError, 'cant find couterpart'):
            checker.check('())')
