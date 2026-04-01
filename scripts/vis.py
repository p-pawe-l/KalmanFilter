import typing
import dataclasses


one_dim_state = tuple[float, float, float]

# Can call proc there and in C put output to stdout and read it here 
# to process it as a plot for example 


@typing.final
class ProbingProgram:
    def __init__(self, program_path: str) -> None:
        self.program_path: str = program_path

    def get_probe(self) -> typing.Sequence[float]:
        pass


@typing.final
class MultiDimObject:
    def __init__(self, probing_program: str, steps: int) -> None:
        self.states: typing.Sequence[one_dim_state] = states
        self.steps: int = steps

        self.proc = subprocess.Popen()

    def run_sim(self) -> None:
        pass

        
    
    
